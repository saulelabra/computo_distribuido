#include <vector>
#include <iostream>
#include <random>
#include <omp.h>

using namespace std;

class vect
{
public:
  vector <double> myVector;
  int N;

  vect(){};

  vect(int N)
  {
    this->N = N;
    myVector.resize(N);
    cout<<"Vector de tamanio: "<<N<<endl;
  }

  void populate(unsigned int tiempoSemilla, int rango)
  {
    int i,j;
    unsigned int seed = time(NULL);

    #pragma omp parallel private(i, j)
    {
      srand(pow(time(NULL), omp_get_thread_num()));

      #pragma omp for
      for(i=0; i<N; i++)
      {
          myVector[i]= rand_r(&seed)%rango;
      }
    }
    cout << "Se lleno el vector" << endl;
  }

  void printVector()
  {
      for(int i=0; i<N; i++)
      {
        cout << myVector[i] << endl;
      }
      cout << endl;
  }

  vect suma(vect B)
  {
      if (N == B.N) {
          int i, j;
          vect  C(N);
          #pragma omp parallel shared(B, C)
          {
            #pragma omp for private(i, j)
            for(i=0; i<N; i++)
            {
                C.myVector[i] += myVector[i] + B.myVector[i];
            }
          }
          return C;
      }else{
          cout<<"Debe de ser igual el tamanio de los vectores"<<endl;
          return *this;
      }

  }
};
