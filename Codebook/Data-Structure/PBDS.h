gp_hash_table<T, T> h;

tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> tr;
tr.order_of_key(x); // find x's ranking
tr.find_by_order(k); // find k-th minimum, return iterator 

