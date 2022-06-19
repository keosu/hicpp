#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/vector.hpp>
#include <fstream>
#include <vector>
using namespace std; 

struct MyRecord {
  uint8_t x, y;
  float z;

  template <class Archive>
  void serialize(Archive& ar) {
    ar(x, y, z);
  }
};

struct SomeData {
  int32_t id;
  vector<int> vec; 
  std::shared_ptr<std::unordered_map<uint32_t, MyRecord>> data;

  template <class Archive>
  void save(Archive& ar) const {
    ar(data);
    ar(vec);
  }

  template <class Archive>
  void load(Archive& ar) {
    static int32_t idGen = 0;
    id = idGen++;
    ar(data);
    ar(vec);
  }
};

int main() {
  {
    std::ofstream os("out.cereal", std::ios::binary);
    cereal::BinaryOutputArchive archive(os);

    SomeData myData;
    myData.vec.push_back(3);
    myData.vec.push_back(5);
    myData.vec.push_back(6);
    archive(myData);
    os.close();
  }
  {
    std::ifstream ifs("out.cereal", std::ios::binary);
    cereal::BinaryInputArchive iarchive(ifs);  // Create an input archive​​
    SomeData dataRB;
    iarchive(dataRB);  // Read the data from the archive​​
    ifs.close();
    cout << "vec size: " <<  dataRB.vec.size() << "\n";
    for(auto& i: dataRB.vec){
        cout << i << " ";
    }
  }
  return 0;
}