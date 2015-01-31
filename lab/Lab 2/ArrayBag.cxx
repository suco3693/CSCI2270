//
#include <cstddef>

// Constructor; creates and initializes an empty Bag
template <class ItemType>
ArrayBag<ItemType>::ArrayBag()
{
	itemCount = 0;
}

// Return the number of Items being stored in the Bag
template <class ItemType>
int ArrayBag<ItemType>::getCurrentSize() const
{
	return itemCount;
}

// Return the capacity of the bag (the maximum Items it can store) 
template <class ItemType>
int ArrayBag<ItemType>::getCapacity( ) const
{
	return DEFAULT_CAPACITY;
}

// Report whether the Bag is empty
// Return true if the Bag is empty (storing no Items);
// Return false if Items exist in the Bag
template <class ItemType>
bool ArrayBag<ItemType>::isEmpty() const
{
	if (itemCount == 0)
	{
		return true;
	}
	else
	{
		return false;
	}		
}

// Report whether the Bag is full
// Return true if the Bag is filled to capacity
// Return false if there is still room
template <class ItemType>
bool ArrayBag<ItemType>::isFull() const
{
	if (itemCount == DEFAULT_CAPACITY)
	{
		return true;
	}	
	else
	{
		return false;
	}	
}

// Give the Bag a new Item to store
// If Bag is full, nothing changes
// Else, Bag must add this Item to its Item array and update its itemCount
// If Bag is full after this, return true; else return false
template <class ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newItem)
{
	bool AddRoom =(itemCount < DEFAULT_CAPACITY);
	if (AddRoom)
	{
		items[itemCount]=newItem;
		itemCount++;
	}
	return AddRoom;
}

// Make the Bag act like an empty Bag again
template <class ItemType>
void ArrayBag<ItemType>::clear()
{
	itemCount=0;
}

// Remove an Item from the bag
// If Item is not there, nothing changes and we return false
// Else, we fill in its spot in that Item array and count number of Items down
template <class ItemType>
bool ArrayBag<ItemType>::remove(const ItemType& anItem)
{
	int locatedIndex=contains(anItem);
	bool Remove=!isEmpty() && (locatedIndex > 0);
	if (Remove)
	{
		itemCount=itemCount-1;
		items[locatedIndex]=items[itemCount];
	}
	return Remove;
}

// Check if an Item is in the Bag
// Return true if it is in the Bag, and false if not
template <class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anItem) const
{
	return getFrequencyOf(anItem) > 0;
}

// Check how many times an Item is in the Bag
// return 0 if it's not there; otherwise,
// return the number of times it occurs
//int countFrequency( const ItemType& target, int searchIndex) const
template <class ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anItem) const
{
	int frequency =0;
	int ArrayIndex=0;
	while (ArrayIndex< itemCount)
	{
		if(items[ArrayIndex] == anItem)
		{
			frequency++;
		}
		ArrayIndex++;
	}		
	return frequency;
}

// Make an output vector of Items from the bag (for checking)
template <class ItemType>
vector<ItemType> ArrayBag<ItemType>::toVector() const
{
	vector<ItemType> bagContents;
	for (int i=0;i<itemCount;i++)
		bagContents.push_back(items[i]);
	return bagContents;				
}
