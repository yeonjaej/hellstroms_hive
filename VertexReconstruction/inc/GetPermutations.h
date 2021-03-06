

#ifndef GETPERMUTATIONS_H
#define GETPERMUTATIONS_H

#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"


class Permutations {
  
 public:

  void AddParameter(std::string const & name,
		    int const inc,
		    double const min, 
		    double const max);

  void AddParameter(std::string const & name,
		    double const set_value);

  void Get();

  void SetParameterNames(std::vector<std::string> const & names);
  void AddPermutation(std::vector<double> const & permutation);
  std::vector<std::vector<double>> const & GetV(); 

  void WriteFile(std::string const & file_name,
		 std::pair<size_t, size_t> const & index_range);
  void GetFiles(std::string const & file_name, int const job_number = 1);
  std::vector<std::vector<double>> const & ReadFile(char const * file_name);
  void WritePermutationTreeToFile();
 
  void Check();
  std::string GetString(size_t const i);

 private:

  std::vector<std::string> parameter_name;
  std::vector<double> parameter_set;
  std::vector<double> parameter_min;
  std::vector<double> parameter_max;
  std::vector<double> parameter_inc;
  std::vector<double> parameter_inc_size;
  std::vector<std::vector<double>> permutation_v;

};

#endif
