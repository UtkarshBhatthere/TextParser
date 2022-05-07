# <ins> QIT #1 Summary Improvement Task </ins>

## <ins> Contents </ins>
 - [Proposition](#proposition) 
 - [Effort Analysis](#effort-analysis)
 - [Code Description](#code-description)
 - [Author Notes](#author-notes)

 ### Proposition
 The current output of word_stat (word statistics by parser) is limited to only displaying the Total word count and Total Unique word count. This limited information is not sufficient to describe the overall textbase that has been parsed. The proposition is to have a separate live vector (list) of same word-count pairs but in an ascending order of count. Further inserts would be performed in a batchwise mergesort fashion. This will allow for the parser to (at all times) have a holistic view of how the words are distributed.

 ### Effort Analysis
 | Description | LoCs | Author |
 | ----------- | ---- | ------ |
 | Addition of another vector to contain the sorted list of word->count pair, related sorted CRUD code | 150 | Utkarsh Bhatt |
 | Word Stat pretty printing | 50 | Utkarsh Bhatt |

 ### Code Description
 Files Added:
    1. containerHelper.hpp: Contains Helper functions for different std containers for miscellaneous tasks.

 Overall Implementation Description:
 A new data member is added to the Parser Class, this sorted vector is how we fetch the most and least frequent words of the wordmap. Since the parser design is reetrant, i.e. the parser can be called repetetively on succesive blobs of txt and update the wordmap, the vector also needs to be updated everytime a new batch is passed, for this, a batch wise design is implemented and std::merge is used to merge two already sorted vectors (class member sorted vector and batch sorted vector).

 ### Author Notes
 One catch with the sorting process is that since the map is a lexically ordered container, The most and least frquent words are sorted on 2 basis, lexicality and count, where count takes priority ofcourse. It means, if ther are 2 words "Apple" and "Hello" both with frequency 15 competing for the 5th most frequent word, "Apple" would be chosen since it comes prior lexically (dictionary sort).
 Author: Utkarsh Bhatt (utkarsh_bhatt@outlook.com)