/*
 * @Author: Jiahui Tang
 * @Date: 2022-06-27 19:55:46
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-07-13 20:35:11
 * @Description:
 */
#include <highgui.hpp>
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
int main()
{
	spdlog::set_level(3);
	// Use the default logger (stdout, multi-threaded, colored)
	spdlog::info("Hello, {}!", "World");
}