#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	ifstream reader_file; // ��ʼ��������
	ofstream write_file; // ��ʼ�������
	string path = "D://test/test.txt"; // �ļ�·��
	string outPath = "D://test/result.txt"; // �ļ�·��

	// ���ļ�
	write_file.open(outPath);
	// ����������򴴽�
	if (!write_file.is_open()) {
		string command = "mkdir -p " + outPath;
		system(command.c_str());
	}

	// ���ļ�
	reader_file.open(path);
	// �ж��Ƿ��ܴ�
	if (!reader_file.is_open()) {
		cout << "�ļ��޷���!" << endl;
		return 0;
	}

	// ��ȡ�ļ�����
	char save_words[10000];
	while (reader_file.getline(save_words, 10000)) {
		string content = save_words;

		// ��ȡfield
		int field_start = content.find("field: '");
		int field_end = content.find("',", field_start);
		string field = content.substr(field_start + 8, field_end - field_start - 8);

		// ��ȡtitle
		int title_start = content.find("title: '");
		int title_end = content.find("',", title_start);
		string title = content.substr(title_start + 8, title_end - title_start - 8);

		// ��ȡfixed
		int fixed_start = content.find("fixed: '");
		int fixed_end = content.find("',", fixed_start);
		string fixed = content.substr(fixed_start + 8, fixed_end - fixed_start - 8);

		// ��ȡminWidth
		int min_width_start = content.find("minWidth: ");
		string min_width = content.substr(min_width_start + 10, 3);

		// ȥ��min_width�еĶ��ය�źͿո�
		if (min_width.find(" ") != -1 || min_width.find(",") != -1) {
			int len = sizeof(min_width);
			min_width = min_width.substr(0, 2);
		};

		// ��������
		int index = content.rfind(" },");
		string insert_content;
		insert_content = "{ title: '" + title + "', field: '" + field + "_father',";
		insert_content += "\n    children: [{ title: total." + field + ", field: '" +
							field + "', minWidth: " + min_width + ", sortable: true }]\n},";

		// ���ļ���д���ļ���
		write_file << insert_content << endl;
	};

	// �ر������
	write_file.close();
	// �ر�������
	reader_file.close();

	return 0;
}