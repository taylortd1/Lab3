//You will need to add one or more typedefs and
//declarations for whatever structure you use to hold
//your ngrams. You will also need to add prototypes
//for any new methods you add to the class.

#define SIZE 10000

struct Ngram
{
      std::string str;
      int count;
      struct Ngram * next;
};
typedef struct Ngram NgramBucket;	

class Ngrams 
{
   private: 
      int ngramSz;
      void insertNgram(std::string s);
      Ngram * hashMap[SIZE];
      Ngram * sorted[SIZE];
      int hash(std::string &s);
      bool find(std::string s);
   public:
      Ngrams(int ngramSz, WordList & wl);
      ~Ngrams();
      void addIncreasing(NgramList *);
      void addDecreasing(NgramList *);
      void sort();
};

