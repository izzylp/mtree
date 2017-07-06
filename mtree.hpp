#ifndef _MTREE_HPP_
#define _MTREE_HPP_

#include <cstdint>
#include <memory>
#include <vector>
#include <algorithm>

template <class T>
class mtree
{
public:
	mtree();
	mtree(const T&);
	mtree(mtree *, const T&);
	mtree *get_parent() const;
	bool has_children() const;
	size_t get_children_count() const;
	size_t get_descendants_count() const;
	mtree *get_child(size_t) const;
	void push_back(mtree *);
	void insert(size_t, mtree *);
	void erase(size_t);
	size_t get_index() const;
	bool is_sibling(const mtree *) const;
	void disconnect();

private:
	size_t get_index(const mtree *) const;
	size_t get_descendants_count(const mtree *) const;
	void disconnect(mtree *);

private:
	/* forbidden operations */
	mtree(mtree&);
	mtree& operator=(mtree&);

private:
	mtree *parent_;
	std::vector<mtree*> children_;
	T data_;
};

template <class T> 
mtree<T>::mtree()
{
	parent_ = nullptr;
}

template <class T> 
mtree<T>::mtree(const T& data_)
{
	this->parent_ = nullptr;
	this->data_ = data_;
}

template <class T> 
mtree<T>::mtree(mtree *parent_, const T& data_)
{
	this->parent_ = parent_;
	this->data_ = data_;
	this->parent_->children_.push_back(this);
}

template <class T> mtree<T> *
mtree<T>::get_parent() const
{
	return parent_;
}

template <class T> bool 
mtree<T>::has_children() const
{
	return (children_.size() != 0);
}

template <class T> size_t 
mtree<T>::get_children_count() const
{
	return children_.size();
}

template <class T> size_t 
mtree<T>::get_descendants_count(const mtree *node) const
{
	size_t ret = 1;

	for (auto it = node->children_.begin(); it != node->children_.end(); ++it) {
		ret += get_descendants_count(*it);
	}
	
	return ret;
}

template <class T> size_t 
mtree<T>::get_descendants_count() const
{
	return get_descendants_count(this) - 1;
}

template <class T> mtree<T> *
mtree<T>::get_child(size_t i) const
{
	return children_[i];
}

template <class T> void 
mtree<T>::push_back(mtree<T> *child)
{
	children_.push_back(child);
	child->parent_ = this;
}

template <class T> void 
mtree<T>::insert(size_t i, mtree<T> *child)
{
	children_.insert(children_.begin() + i, child);
	child->parent_ = this;
}

template <class T> void 
mtree<T>::erase(size_t i)
{
	children_.erase(children_.begin() + i); 
}

template <class T> bool 
mtree<T>::is_sibling(const mtree<T> *parent_) const
{
	return (parent_ == this->parent_);
}

template <class T> size_t 
mtree<T>::get_index() const
{
	return get_index(this);
}

template <class T> size_t 
mtree<T>::get_index(const mtree *child) const
{
	mtree *tmp = child->parent_;
	return (std::find(tmp->children_.begin(), tmp->children_.end(), child) - tmp->children_.begin());
}

template <class T> void 
mtree<T>::disconnect(mtree<T> *node)
{
	parent_->erase(get_index(node));
	node->parent_ = nullptr;
}

template <class T> void 
mtree<T>::disconnect()
{
	disconnect(this);
}

#endif
