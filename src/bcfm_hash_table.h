#ifndef BC_FLAT_MAP
#define BC_FLAT_MAP

#include "hash_table.h"
#include <boost/unordered/concurrent_flat_map.hpp>



struct bcfm_hash_table {
  bcfm_hash_table(int capacity, int thread_count)
  { 
   m_table.reserve(capacity);
  }

  std::pair<int, bool> search(int key, int tid) {
    int o;
    bool found = m_table.visit(key, [&](const auto& x) {
      o = x.second;
    });
    if (found) {
      return std::make_pair(o, true);
    } else {
      return std::make_pair(0, false);
    }
  }

  void insert(int key, int val, int tid) {
    m_table.emplace(key, val);
  }

  void remove(int key, int tid) {
    m_table.erase(key);
  }

private:
  boost::unordered::concurrent_flat_map<int, int> m_table;

};

#endif
