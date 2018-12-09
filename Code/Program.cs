using System;
using System.Collections.Generic;

namespace The_Code.Code1
{
    class Program
    {
        static Dictionary<string, char> table = new Dictionary<string, char>();

        static void Main(string[] args)
        {
            // 初始化摩斯电码表
            table["._"] = 'A'; table["_..."] = 'B'; table["_._."] = 'C'; table["_.."] = 'D'; table["."] = 'E';
            table[".._."] = 'F'; table["__."] = 'G'; table["...."] = 'H'; table[".."] = 'I'; table[".___"] = 'J';
            table["_._"] = 'K'; table["._._."] = 'L'; table["__"] = 'M'; table["_."] = 'N'; table["___"] = 'O';
            table[".__."] = 'P'; table["__._"] = 'Q'; table["._."] = 'R'; table["..."] = 'S'; table["_"] = 'T';
            table[".._"] = 'U'; table["..._"] = 'V'; table[".__"] = 'W'; table["_.._"] = 'X'; table["_.__"] = 'Y';
            table["__.."] = 'Z';

            // 输入莫斯电码
            string str = Console.ReadLine();
            str += " ";
            string s = "";
            string showStr = "";
            // 拆解莫斯电码
            for (int i = 0; i < str.Length; i++)
            {
                if (str[i] == ' ')
                {
                    char c;
                    table.TryGetValue(s, out c);
                    showStr += c;
                    s = "";
                }
                else
                {
                    s += str[i];
                }
            }

            // read ... ___ ...
            // write SOS
            Console.WriteLine(showStr);
        }
    }
}
