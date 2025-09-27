#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

const size_t MAX_CACHE_SIZE = 200;

class IdealCache
{
private:

    struct CacheCell
    {
        int key;        // = val
        int next_pos;

        bool operator<(const CacheCell& other) const        //чтобы можно было сравнивать
        {
            return next_pos < other.next_pos;
        }
    };

    std::vector<int> requests;      //список запросов элементов
    std::set<CacheCell> cache_set;
    std::unordered_map<int, std::set<CacheCell>::iterator> cells_table;         //обеспечивает быстрый доступ к элементам кэша, по ключу дается ссылка на ячейку
    size_t capacity;

    using iterator = std::set<CacheCell>::iterator;

public:

    IdealCache(size_t capacity, std::vector<int> requests) : capacity(capacity), requests(requests) {}

    void cache_push(int key, size_t pos)
    {
        iterator new_cell_it;
        auto it = cells_table.find(key);
        if (it == cells_table.end())
        {
            //промах, нужно проверить, есть ли свободное место
            if (cache_set.size() >= capacity)
            {
                //места нет, надо вытеснить, нам просто найти элемент с самым больщим значением next_use, потому что мы используем set, этот элемемнт будет в самом начале
                auto del_cell = cache_set.begin();
                cells_table.erase(del_cell->key);
                cache_set.erase(del_cell);
            }

            //теперь нужно добавить новый элемент, set автоматически его поставит, нужно только засунуть его туда
            //у нас уже есть конструктор, теперь используем список иницаализации, создаем новую ячейку
            CacheCell new_cell{key, find_next_pos(key, pos + 1)};
            new_cell_it = cache_set.insert(new_cell).first;    //first - итератор, second - bool был ли вставлен
            
        }
        else
        {
            //нужно поменять в нужной ячейке значение следующего появления
            //но это set -> мы не можем просто заменить значение по которому идет упорядочивание, нам нужно стереть предыдущее поле и вставить новое
            CacheCell the_cell = *it->second;
            cache_set.erase(it->second);

            the_cell.next_pos = find_next_pos(key, pos + 1);
            new_cell_it = cache_set.insert(the_cell).first;
        }
        cells_table[key] = new_cell_it;

    }

private:

    int find_next_pos(int key, size_t pos)
    {
        //от заданной позиции пройти по следующим элементам до конца, пока не кончится вектор
        for (int i = pos; i < requests.size(); i++)
        {
            if (key == requests[i])
                return i;
        }

        return MAX_CACHE_SIZE;
    }
};
