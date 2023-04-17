struct Node {
	int hit = 0;
	Node *next[26];
	// 26 is the size of the set of characters
	// a - z
	Node(){
		for(int i = 0; i < 26; i++)
			next[i] = NULL;
	}
};

void insert(string &s, Node *node){
	// node cannot be null
	for(char v : s){
		if(node->next[v - 'a'] == NULL)
			node->next[v - 'a'] = new Node;
		node = node->next[v - 'a'];
	}
	node->hit++;
}
