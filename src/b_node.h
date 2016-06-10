#ifndef __B_NODE_H
#define __B_NODE_H

class BlockFile;
class BTree;

// -----------------------------------------------------------------------------
//  BNode: basic structure of node in b-tree
// -----------------------------------------------------------------------------
class BNode {
public:
	BNode();						// constructor
	virtual ~BNode();				// destructor

	// -------------------------------------------------------------------------
	virtual void init(				// init a new node, which not exist
		int level,						// level (depth) in b-tree
		BTree* btree);					// b-tree of this node

	virtual void init_restore(		// load an exist node from disk to init
		BTree* btree,					// b-tree of this node
		int block);						// address of file of this node

	// -------------------------------------------------------------------------
	virtual void read_from_buffer(	// read a b-node from buffer
		char* buf);						// store info of a b-node

	virtual void write_to_buffer(	// write a b-node into buffer
		char* buf);						// store info of a b-node

	// -------------------------------------------------------------------------
	virtual int get_entry_size();	// get entry size in b-node

									// find pos just less than input key
	virtual void find_position_by_key(
		float key,
		int& low_pos,
		int& high_pos);						

	virtual float get_key(			// get <key> indexed by <index>
		int index);						// index

	// -------------------------------------------------------------------------
									// get left sibling node
	virtual BNode* get_left_sibling();
									// get right sibling node
	virtual BNode* get_right_sibling();

	// -------------------------------------------------------------------------
	int get_block() const;				// get <block_>

	int get_num_entries() const;			// get <num_entries_>

	int get_level() const;				// get <level_>

	// -------------------------------------------------------------------------
	static int  get_header_size();			// get header size in b-node

	float get_key_of_node() const;			// get key of this node

	bool isFull() const;					// whether is full?

	// -------------------------------------------------------------------------
	void set_left_sibling(			// set <left_sibling>
		int left_sibling);				// addr of left sibling node

	void set_right_sibling(			// set <right sibling>
		int right_sibling);				// addr of right sibling node

protected:
	// -------------------------------------------------------------------------
	char   level_;					// level of b-tree (level > 0)
	int    num_entries_;			// number of entries in this node
	int    left_sibling_;			// addr in disk for left  sibling
	int    right_sibling_;			// addr in disk for right sibling
	float* value_;					// keys

	// -------------------------------------------------------------------------
	bool   dirty_;					// if dirty, write back to file
	int    block_;					// addr of disk for this node
	int    capacity_;				// max num of entries can be stored
	BTree* btree_;					// b-tree of this node
};

// -----------------------------------------------------------------------------
//  BIndexNode: structure of index node in b-tree
// -----------------------------------------------------------------------------
class BIndexNode : public BNode {
public:
	BIndexNode();					// constructor
	virtual ~BIndexNode();			// destructor

	// -------------------------------------------------------------------------
	void init(				// init a new node, which not exist
		int level,						// level (depth) in b-tree
		BTree* btree) override;					// b-tree of this node

	void init_restore(		// load an exist node from disk to init
		BTree* btree,					// b-tree of this node
		int block) override;						// address of file of this node

	// -------------------------------------------------------------------------
	void read_from_buffer(	// read a b-node from buffer
		char* buf) override;						// store info of a b-node

	void write_to_buffer(	// write a b-node into buffer
		char* buf) override;						// store info of a b-node

	// -------------------------------------------------------------------------
	int get_entry_size() override;	// get entry size in b-node

									// find pos just less than input key
	void find_position_by_key(
		float key,
		int& low_pos,
		int& high_pos) override;

	float get_key(			// get <value_> indexed by <index>
		int index) override;						// index

	// -------------------------------------------------------------------------
									// get left sibling node
	BIndexNode* get_left_sibling() override;	
									// get right sibling node
	BIndexNode* get_right_sibling() override;

	// -------------------------------------------------------------------------
	int get_son(					// get <son_> indexed by <index>
		int index) const;						// index

	// -------------------------------------------------------------------------
	void add_new_child(				// add new child by its child node
		float key,						// input key
		int son);						// input son

protected:
	int* son_;						// addr of son node
};


// -----------------------------------------------------------------------------
//  BLeafNode: structure of leaf node in b-tree
// -----------------------------------------------------------------------------
class BLeafNode : public BNode {
public:
	BLeafNode();					// constructor
	virtual ~BLeafNode();			// destructor

	// -------------------------------------------------------------------------
	void init(				// init a new node, which not exist
		int level,						// level (depth) in b-tree
		BTree* btree) override;					// b-tree of this node

	void init_restore(		// load an exist node from disk to init
		BTree* btree,					// b-tree of this node
		int block) override;						// address of file of this node

	// -------------------------------------------------------------------------
	void read_from_buffer(	// read a b-node from buffer
		char* buf) override;						// store info of a b-node

	void write_to_buffer(	// write a b-node into buffer
		char* buf) override;						// store info of a b-node

	// -------------------------------------------------------------------------
	int get_entry_size() override;	// get entry size in b-node

									// find pos just less than input key
	void find_position_by_key(
		float key,
		int& low_pos,
		int& high_pos) override;

	float get_key(			// get <value_> indexed by <index>
		int index) override;						// index

	// -------------------------------------------------------------------------
									// get left sibling node
	BLeafNode* get_left_sibling() override;
									// get right sibling node
	BLeafNode* get_right_sibling() override;

	// -------------------------------------------------------------------------
	int get_key_size(				// get key size of this node
		int block_length);				// block length

	int get_increment();			// get <increment>

	int get_num_keys() const;				// get <num_keys_>

	int get_entry_id(				// get entry id indexed by <index>
		int index) const;						// index

	// -------------------------------------------------------------------------
	void add_new_child(				// add new child by input id and key
		int id,							// input object id
		float key);						// input key

protected:
	int  num_keys_;					// number of keys
	int* index_;						// object id

	int capacity_keys_;				// max num of keys can be stored
};

#endif
