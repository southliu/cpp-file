#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	ifstream reader_file; // 初始化输入流
	ofstream write_file; // 初始化输出流
	string path = "D://test/test.txt"; // 文件路径
	string outPath = "D://test/result.txt"; // 文件路径

	// 打开文件
	write_file.open(outPath);
	// 如果不存在则创建
	if (!write_file.is_open()) {
		string command = "mkdir -p " + outPath;
		system(command.c_str());
	}

	// 打开文件
	reader_file.open(path);
	// 判断是否能打开
	if (!reader_file.is_open()) {
		cout << "文件无法打开!" << endl;
		return 0;
	}

	// 读取文件内容
	char save_words[10000];
	while (reader_file.getline(save_words, 10000)) {
		string content = save_words;

		// 获取field
		int field_start = content.find("field: '");
		int field_end = content.find("',", field_start);
		string field = content.substr(field_start + 8, field_end - field_start - 8);

		// 获取title
		int title_start = content.find("title: '");
		int title_end = content.find("',", title_start);
		string title = content.substr(title_start + 8, title_end - title_start - 8);

		// 获取fixed
		int fixed_start = content.find("fixed: '");
		int fixed_end = content.find("',", fixed_start);
		string fixed = content.substr(fixed_start + 8, fixed_end - fixed_start - 8);

		// 获取minWidth
		int min_width_start = content.find("minWidth: ");
		string min_width = content.substr(min_width_start + 10, 3);

		// 去除min_width中的多余逗号和空格
		if (min_width.find(" ") != -1 || min_width.find(",") != -1) {
			int len = sizeof(min_width);
			min_width = min_width.substr(0, 2);
		};

		// 插入数据
		int index = content.rfind(" },");
		string insert_content;
		insert_content = "{ title: '" + title + "', field: '" + field + "_father',";
		insert_content += "\n    children: [{ title: total." + field + ", field: '" +
							field + "', minWidth: " + min_width + ", sortable: true }]\n},";

		// 将文件流写入文件中
		write_file << insert_content << endl;
	};

	// 关闭输出流
	write_file.close();
	// 关闭输入流
	reader_file.close();

	return 0;
}