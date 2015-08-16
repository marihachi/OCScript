#pragma once
using namespace std;

#include <vector>
#include <sstream>

namespace OCScript
{
	// 文字列操作を便利にする機能をまとめたクラスです。
	class StringUtility
	{
	public:

		// 区切り文字により文字列をスプリットします。
		// 引数: ソース文字列, 区切り文字
		static vector<wstring> Split(const wstring &src, wchar_t delimiter)
		{
			wstringstream ss(src);
			vector<wstring> items;
			wstring item;

			while (getline(ss, item, delimiter))
				items.push_back(item);

			return items;
		}

		// 区切り文字により文字列を連結します。
		// 引数: ソース文字列, 区切り文字
		static wstring Join(const vector<wstring> &src, wstring delimiter)
		{
			wstring dest;

			for (auto it = src.begin(); it != src.end(); it++)
			{
				dest += *it;

				if (it != src.end() - 1)
					dest += delimiter;
			}

			return dest;
		}

		// 文字列を置換して新しい文字列として返します。
		// 引数: ソース文字列, 対象の文字列, 置換後の文字列
		static wstring Replace(const wstring src, const wstring oldVal, const wstring newVal)
		{
			auto temp = src;
			wstring::size_type pos(temp.find(oldVal));

			while (pos != wstring::npos)
			{
				temp.replace(pos, oldVal.length(), newVal);
				pos = temp.find(oldVal, pos + newVal.length());
			}

			return temp;
		}
	};
}
