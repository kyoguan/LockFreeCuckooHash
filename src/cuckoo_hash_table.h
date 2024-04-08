#ifndef CUCKOO_HASH_TABLE
#define CUCKOO_HASH_TABLE

#include "hash_table.h"
#include "../../../libcuckoo/install/include/libcuckoo/cuckoohash_map.hh"


struct cuckoo_hash_table {
  cuckoo_hash_table(int capacity, int thread_count)
  { 
   m_table.reserve(capacity*2);
  }

  std::pair<int, bool> search(int key, int tid) {
    int out;
    if(m_table.find(key, out)) {
      return std::make_pair(out, true);
    } else {
      return std::make_pair(0, false);
    }
  }

  void insert(int key, int val, int tid) {
    m_table.insert(key, val);
  }

  void remove(int key, int tid) {
    m_table.erase(key);
  }

private:
  libcuckoo::cuckoohash_map<int, int> m_table;

};

#endif
