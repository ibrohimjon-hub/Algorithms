#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
    ListItem *prev;
    bool sentinel;
};

struct List
{
    ListItem sentinel;

    List() : sentinel{Data(), nullptr, nullptr, true}
    {
        sentinel.next = &sentinel;
        sentinel.prev = &sentinel;
    }
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    while (list_erase_first(list) != nullptr)
    {
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->sentinel.next == &list->sentinel ? nullptr : list->sentinel.next;
}

ListItem *list_last(List *list)
{
    return list->sentinel.prev == &list->sentinel ? nullptr : list->sentinel.prev;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next->sentinel ? nullptr : item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return item->prev->sentinel ? nullptr : item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    return list_insert_after(list, nullptr, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *next = item == nullptr ? list->sentinel.next : item->next;
    ListItem *added = new ListItem{data, next, item == nullptr ? &list->sentinel : item, false};
    added->prev->next = added;
    next->prev = added;
    return added;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, nullptr);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem *removed = item == nullptr ? list->sentinel.next : item->next;
    if (removed == &list->sentinel)
    {
        return nullptr;
    }
    ListItem *next = removed->next;
    removed->prev->next = next;
    next->prev = removed->prev;
    delete removed;
    return next->sentinel ? nullptr : next;
}
