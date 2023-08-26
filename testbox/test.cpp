#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>  // 如果使用了 open
#include <linux/videodev2.h>

int main() {
    // 打开UVC设备
    int fd = open("/dev/video0", O_RDWR);
    if (fd == -1) {
        perror("Cannot open video device");
        return 1;
    }

    // 查询设备能力
    struct v4l2_capability cap;
    if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == -1) {
        perror("Cannot query capabilities");
        close(fd);
        return 1;
    }
    printf("Driver: %s\n", cap.driver);

    // 设置视频捕获格式
    struct v4l2_format format;
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_YUV420;
    format.fmt.pix.width = 640;
    format.fmt.pix.height = 480;
    int io_result = ioctl(fd, VIDIOC_S_FMT, &format);
    if (io_result == -1) {
        perror("Cannot set format");
        close(fd);
        return 1;
    }

    // 请求缓冲区
    struct v4l2_requestbuffers req;
    req.count = 1;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    if (ioctl(fd, VIDIOC_REQBUFS, &req) == -1) {
        perror("Cannot request buffers");
        close(fd);
        return 1;
    }

    // 映射缓冲区
    struct v4l2_buffer buf;
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;
    if (ioctl(fd, VIDIOC_QUERYBUF, &buf) == -1) {
        perror("Cannot query buffer");
        close(fd);
        return 1;
    }
    void *buffer_start = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
    if (buffer_start == MAP_FAILED) {
        perror("Cannot map buffer");
        close(fd);
        return 1;
    }

    // 开始捕获
    if (ioctl(fd, VIDIOC_STREAMON, &buf.type) == -1) {
        perror("Cannot start capture");
        close(fd);
        return 1;
    }

    // 将缓冲区加入队列
    if (ioctl(fd, VIDIOC_QBUF, &buf) == -1) {
        perror("Cannot queue buffer");
        close(fd);
        return 1;
    }

    // 从队列中取出缓冲区
    if (ioctl(fd, VIDIOC_DQBUF, &buf) == -1) {
        perror("Cannot dequeue buffer");
        close(fd);
        return 1;
    }

    // 这里可以处理图像数据（存储在buffer_start指向的内存中）

    // 停止捕获
    if (ioctl(fd, VIDIOC_STREAMOFF, &buf.type) == -1) {
        perror("Cannot stop capture");
        close(fd);
        return 1;
    }

    // 释放缓冲区
    munmap(buffer_start, buf.length);

    // 关闭设备
    close(fd);

    return 0;
}
