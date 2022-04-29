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
 | Addition of another vector to contain the sorted list of word->count pair, Mergesort implementation of batch wise list merge. | 200 | Utkarsh Bhatt |
 | Word Stat pretty printing | 50 | Utkarsh Bhatt |

 ### Code Description
 ### Author Notes