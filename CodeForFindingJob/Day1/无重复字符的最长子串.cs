// 给定一个字符串 s ，请你找出其中不含有重复字符的 最长  的长度。

public class Solution {
    public int LengthOfLongestSubstring(string s) {
        int startPosition = 0;
        int result = 0;
        Hashtable hashTable = new Hashtable();
        for(int posNo =0;posNo<s.Length;posNo++)
        {
            if(!hashTable.Contains(s[posNo]))
            {
                hashTable.Add(s[posNo],posNo);
                result = Math.Max(result,hashTable.Count);
            }
            else
            {
                int newStartPosition = (int)(hashTable[s[posNo]])+1;
                for(int i =startPosition;i<newStartPosition;i++)
                {
                    hashTable.Remove(s[i]);
                }
                hashTable.Add(s[posNo],posNo);
                startPosition = newStartPosition;
            }
        }
        return result;
    }
}