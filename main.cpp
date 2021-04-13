#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <limits.h>

class DependenciesTable;
class Course;
class PoolDependencies;

class Course {
 public:
  
  Course() {}
  
  Course(int level, const std::string& str, int priority) : level(level), name(str), priority(priority) {}
  
  std::string& GetName() { return name; }
  
  int GetLevel() const { return level; }
  
  void AddPoolDependencies(PoolDependencies& depend) { dependencies.push_back(depend); }
  void AddReversedEdge(Course course) {
    reversed_edges.push_back(course);
  }
  int MaxSemesterToTake() const {
    // Not Implemented
  }
  
  int GetHight() const {
    return height;
  }
  
  int GetUpVertex() const {
    int min_height = std::numeric_limits<int>::max();
    for( const auto& course: reversed_edges) {
      min_height = std::min(course.GetHight(), min_height);
    }
    return min_height;
  }

 private:
  std::string name;
  std::vector<PoolDependencies> dependencies;
  std::vector<Course> reversed_edges;
  int level;
  int height;
  int priority;
  void AddPoolDependence(PoolDependencies& depends) { dependencies.push_back(depends); }
};

class PoolDependencies {
 public:
  PoolDependencies() {}

  void AddCourse(Course course) { pool.push_back(course); }
  std::vector<Course>& GetCources() {
    return pool;
  }; 
 private:
  std::vector<Course> pool;
};

class DependenciesTable {
 public:
  DependenciesTable() {}
  
  Course GetCourseByName(const std::string& name, int level, int priority = -1) {
    if (table.find(name) == table.end()) {
      table[name] = Course(level, name, priority);
    }
    return table.at(name);
  }

 private:
  std::map<std::string, Course> table;
};

bool NextMask(std::vector<bool>& mask) {
  int flag = 1;
  for (int i = 0; i < mask.size(); i++) {
    int new_value = (mask[i] + flag) % 2;
    flag = (flag + mask[i]) / 2;
  }
  return !flag;
}

bool IsSuitableSubset(const std::vector<bool>& mask, const std::vector<std::string>& cources) { 
  std::vector<bool> met(mask.size(), 0);
  for( int i = 0; i < mask.size(); i++ ) {
    if( met[i] == 1 || mask[i] == 0 ) {
      continue;
    }
     
  }
}

bool TryToPlaceInTimeTable(const std::vector<bool>& mask, const std::vector<std::string>& cources) {
  // Not Implemented
}

void CheckPriorityAndSaveTheBest(const std::vector<bool>& mask, const std::vector<bool>& best_mask){
    // Not Implemented
};

void MakeSuitableTimetable(const std::vector<std::string>& cources) {
  std::vector<bool> mask(cources.size(), 0);
  std::vector<bool> best_mask(cources.size(), 0);
  while (NextMask(mask)) {
    IsSuitableSubset(mask, cources);
    if (TryToPlaceInTimeTable(mask, cources)) {
      CheckPriorityAndSaveTheBest(mask, best_mask);
    }
  }
}

int main() {
  int course_number;
  std::cin >> course_number;
  int level;
  std::vector<std::string> cources(course_number);
  DependenciesTable table;
  for (int i = 0; i < course_number; i++) {
    std::cin >> cources[i] >> level;
    Course course(table.GetCourseByName(cources[i], level, i));
    int PoolsCount;
    std::cin >> PoolsCount;
    for (int j = 0; j < PoolsCount; ++j) {
      int CoursesNumberInPool;
      std::cin >> CoursesNumberInPool;
      PoolDependencies Pool;
      for (int k = 0; k < CoursesNumberInPool; ++k) {
        std::string str;
        int level;
        std::cin >> str >> level;
        Pool.AddCourse(table.GetCourseByName(str, level, i));
      }
      course.AddPoolDependencies(Pool);
    }
  }
  MakeSuitableTimetable(cources);
}
