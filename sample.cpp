#include <thread>
#include <future>
#include <vector>
#include <iostream>
#include <iomanip>

long int  calculate_sum(const std::vector <int> &v)
{
  long int sum = 0;
  for(unsigned i = 0 ; i < v.size() ; i ++)
    sum += v[i];
  return sum;
}

std::vector <long int> calculate_row_sum(const std::vector<std::vector <int> > &mat)
{
  std::vector <std::future <long int > > futures(mat.size());
  std::vector <long int> vec_sum;
  unsigned s_mat = mat.size();
  for(unsigned i = 0 ; i < s_mat ; i ++)
    futures[i] = std::async(calculate_sum , mat[i]);
 
  for(unsigned i = 0 ; i < s_mat ; i ++)
  {
    int res = futures[i].get();
    vec_sum.push_back(res);
  }
  return vec_sum;
}

template <typename t>
std::vector <std::vector <t> > read_mat(unsigned rows, unsigned cols)
{
  std::vector<std::vector <t> > mat;
  for(unsigned i = 0 ; i < rows ; i++)
    {
      std::vector <t> row (cols);
      mat.push_back(row);
      for(unsigned j = 0 ; j < cols ; j ++)
	{
	  std::cout<<"elem ["<<i + 1<<"]["<<j + 1<<"] :";
	  std::cin>>mat[i][j];
	}
    }
  return mat;
}

template <typename t>
void write_mat(const std::vector<std::vector <t> > & mat)
{
  for(unsigned i = 0 ; i < mat.size() ; i ++)
    {
      for(unsigned j = 0 ; j < mat[i].size() ; j ++)
	std::cout<<std::setw(5)<<mat[i][j];
      std::cout<<std::endl;
    }
}

template <typename t>
void write_vec(const std::vector <t> &vec)
{
  for (unsigned i = 0 ; i < vec.size() ; i ++)
    std::cout<<vec[i]<<std::endl;
}

int main()
{
  int rows, cols;
  std::cout<<"rows: ";
  std::cin>>rows;
  std::cout<<"cols: ";
  std::cin>>cols;
  std::vector<std::vector <int> > mat = read_mat <int> (rows , cols);
  write_mat <int> (mat);
  std::vector<long int> result = calculate_row_sum(mat);
  write_vec<long int> (result);
  return 0;
}
