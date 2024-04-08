#ifndef L4_HASH_TABLE
#define L4_HASH_TABLE

#include "hash_table.h"
#include "L4/LocalMemory/HashTableService.h"

using namespace L4;
using ht_action              = L4::LocalMemory::EpochManager::Action;
using ht_service             = L4::LocalMemory::HashTableService;
using ht_context             = L4::LocalMemory::Context;
using ht_config              = L4::HashTableConfig;
using ht_table               = L4::IWritableHashTable;
using ht_key		             = ht_table::Key;
using ht_value		           = ht_table::Value;


LocalMemory::HashTableService& getService() {
  static EpochManagerConfig epochConfig{1000, std::chrono::milliseconds(100), 1};
  static LocalMemory::HashTableService service{epochConfig};
  return service;
}

struct L4_hash_table {
  L4_hash_table(int capacity, int thread_count, const char* tname):
  m_idx(getService().AddHashTable(HashTableConfig(tname, HashTableConfig::Setting{1000000}))),
  m_tbl(getService().GetContext()[m_idx]) 
  { 

  }

  std::pair<int, bool> search(int key, int tid) {
      IWritableHashTable::Key k;
      k.m_data = reinterpret_cast<const std::uint8_t*>(&key);
      k.m_size = sizeof(key);
      
      IWritableHashTable::Value v;

      if (m_tbl.Get(k, v)) {
        int rv = *reinterpret_cast<const int*>(v.m_data);

        return std::make_pair(rv, true);
      } else {
        return std::make_pair(0, false);
      } 

  }

  void insert(int key, int val, int tid) {
      IWritableHashTable::Key k;
      k.m_data = reinterpret_cast<const std::uint8_t*>(&key);
      k.m_size = sizeof(key);
      
      IWritableHashTable::Value v;
      v.m_data = reinterpret_cast<const std::uint8_t*>(&val);
      v.m_size = sizeof(val);

      m_tbl.Add(k, v);
  }

  void remove(int key, int tid) {
      IWritableHashTable::Key k;
      k.m_data = reinterpret_cast<const std::uint8_t*>(&key);
      k.m_size = sizeof(key);
      m_tbl.Remove(k);
  }

private:
  size_t   m_idx;
  ht_table& m_tbl;

};

#endif
