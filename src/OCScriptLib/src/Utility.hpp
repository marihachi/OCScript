#pragma once
using namespace std;

#include <vector>
#include <sstream>

namespace OCScript
{
	// 便利な機能をまとめたクラスです。
	class Utility
	{
	public:
		// 区切り文字により文字列をスプリットします。
		// 引数: ソース文字列, 区切り文字
		static vector<string> StrSplit(const string &src, char delimiter)
		{
			stringstream ss(src);
			vector<string> items;
			string item;

			while (getline(ss, item, delimiter))
				items.push_back(item);

			return items;
		}

		// 文字列を置換して新しい文字列として返します。
		// 引数: ソース文字列, 対象の文字列, 置換後の文字列
		static string StrReplace(const string src, const string oldVal, const string newVal)
		{
			auto temp = src;
			string::size_type pos(temp.find(oldVal));

			while (pos != string::npos)
			{
				temp.replace(pos, oldVal.length(), newVal);
				pos = temp.find(oldVal, pos + newVal.length());
			}

			return temp;
		}
	};
}
