#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdlib.h>
#include "baseTypes.h"
#include <cassert>

template <class T> class NodeC
{
public:
	NodeC(T data) { mData = data; mNext = nullptr; mPrev = nullptr; };
	~NodeC() {};

	void SetNext(NodeC* next) { mNext = next; };
	void SetPrev(NodeC* prev) { mPrev = prev; };
	void SetData(T data) { mData = data; };

	void SetNextNull() { mNext = nullptr; };
	void SetPrevNull() { mPrev = nullptr; };

	NodeC* GetNext() { return mNext; };
	NodeC* GetPrev() { return mPrev; };
	T GetData() { return mData; };

private:
	T mData;
	NodeC* mNext;
	NodeC* mPrev;
};

template <class T>
class LinkedListC
{
public:
	LinkedListC() { mSize = 0; mHead = nullptr; mTail = nullptr; };
	~LinkedListC() {};

	NodeC<T>* GetHead() { return mHead; };
	NodeC<T>* GetTail() { return mTail; };
	int32_t GetSize() { return mSize; };

	void SetHeadNull() { mHead = nullptr; };
	void SetTailNull() { mTail = nullptr; };

	// adds a node with data at the end of the list
	bool Append(T data)
	{
		if (mHead == nullptr)
		{
			mHead = new NodeC<T>(data);
			mTail = mHead;
		}
		else
		{
			mTail->SetNext(new NodeC<T>(data));
			NodeC<T>* temp = mTail;
			mTail = temp->GetNext();
			mTail->SetPrev(temp);
		}

		// increment size of list
		mSize++;
		return true;
	};

	// checks list for data and then removes the node from the list and decrement list size
	bool Remove(T data)
	{
		if (mSize <= 0)
		{
			return false;
		}

		// create an iterator pointer to hold the target node
		NodeC<T>* iterator = mHead;

		// get the node with the data
		while (iterator->GetData() != data)
		{
			// if iterator reaches end, exit loop
			if (iterator == mTail) break;

			iterator = iterator->GetNext();
		}

		// if data doesn't match, data doesn't exist
		if (iterator->GetData() != data)
		{
			// early out
			return false;
		}

		// if only value in list
		if (iterator == mTail && iterator == mHead)
		{
			SetHeadNull();
			SetTailNull();
		}

		// remove Next ties
		if (iterator->GetNext() != nullptr)
		{
			iterator->GetNext()->SetPrev(iterator->GetPrev());
		}
		else if (iterator == mTail)
		{
			mTail = iterator->GetPrev();
			mTail->SetNextNull();
		}

		// remove Prev ties
		if (iterator->GetPrev() != nullptr)
		{
			iterator->GetPrev()->SetNext(iterator->GetNext());
		}
		else if (iterator == mHead)
		{
			mHead = iterator->GetNext();
			mHead->SetPrevNull();
		}

		// decrement the size of the list
		mSize--;

		// free iterator pointer memory
		delete(iterator);
		return true;
	};

	// return data at postion
	T Get(int32_t position)
	{
		assert(mSize > 0);
		assert(mSize > position);

		NodeC<T>* iterator = mHead;

		for (int i = 0; i < position; i++)
		{
			iterator = iterator->GetNext();
		}

		return iterator->GetData();
	}

private:
	// points to the start of the list
	NodeC<T>* mHead;

	// points to the end of the list
	NodeC<T>* mTail;

	// holds the size of the list
	int32_t mSize;
};

#endif // !LINKEDLIST_H
