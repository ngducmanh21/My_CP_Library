
struct TrieNode {
  TrieNode* child[26];
  int cnt;
 
  TrieNode() {
    for (int i = 0; i < 26; i++)
      child[i] = NULL;
    cnt = 0;
  }
};
 
TrieNode* root = new TrieNode();
 
void add (const string& s) {
  TrieNode* u = root;
  for (char ch : s) {
    int id = ch - 'a';
    if (u -> child[id] == NULL) {
      u -> child[id] = new TrieNode();
    }
    u = u -> child[id];
  }
  u -> cnt++;
}