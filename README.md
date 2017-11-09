# Approximate-document-matching
In many scenarios, we would like to know how ``similar'' two documents are are to each other. For example, many pages on the web are similar but not entirely identical to each other. Search engines like Google or Bing need to group similar web pages together such that only one among a group of similar documents is displayed in the search result. We refer to this process of measuring document similarity as approximate matching. In this program, it approximately matches one input file against another file.

1. Exact Matching
  It checks whether a document is an exact duplicate of another. However, it will do something slightly more sophisticated by matching documents' raw contents character-by-character. In particular, it ``normalize'' (i.e. clean up) a document by doing the following:
    Convert all upper case letters to lower case ones.
    Convert different white space characters (e.g. carriage return, tab,...) into the space character,
    Shrink any sequence of two or more space characters to exactly one space.
    Remove any whitespace at the beginning and end of the text.

2. Simple Approximate Matching
  "Chop" original string X into m/k non-overlapping substrings (called chunks) and try to match each chunk in Y. For example, if the content of X is "abcd" and k=2, the optimized algorithm only matches 2 chunks ("ab", "cd") instead of 3 substrings as in the original naive algorithm. Doing so cuts down the runtime by a factor of k to O(m*n) Note that this simple algorithm does not produce the exact same score as the naive algorithm in all scenarios, but the resulting score is close enough for practical purposes.
  
3. Rabin-Karp Approximate Matching
  RK checks if a given query string P appears as a substring in Y. RK uses the idea of hashing: A hash function turns a string of arbitary length into a b-bit hash value with the property that collision (two different strings having the same hash value) is unlikely. At a high level, RK works by computing a hash for the query string, hash(P), as well as a hash for each of the n-k+1 substrings of length k in Y, hash(Y[0...k-1]), hash(Y[1...k]), ..., hash(Y[n-k...n-1]), where Y[0...k-1] is the first k characters of Y and Y[1...k] is the second k characters of Y and so on. By comparing hash(P) with each of the n-k+1 hashes from Y, we can determine if P appears as a substring in Y. There are many nice hash functions out there (such as MD5, SHA-1), but unfortunately, none of them would make RK any faster since it takes O(k) time to compute each of the n-k+1 hashes from Y.

  RK's magical ingredient is its invention of a ``rolling'' hash function. Specifically, given hash(Y[i...i+k-1]), RK takes only constant time instead of O(k) time to compute hash(Y[i+1...i+k]).
  
 4. RK Approximate Matching with a Bloom Filter
  A Bloom filter is a bitmap of h bits initialized to zeros in the beginning. We insert all m/k RK hash values of X that we want to match into the ``filter''.
  To insert a value v into the bitmap, we use f hash functions to map v into f positions in the bitmap and set each position to be one. For example, starting with a 10-bit bitmap and f=2, if v is mapped to positions 1,5 and v' is mapped to 3,9, the bitmap after inserting v,v' would be 0101010001. There are many reasonable conventions with which we can use a byte array to represent a bitmap. In this lab, we expect you follow one specific convention and interpret bits in the Big-Endian convention within a byte. For example, we use a 2 byte array to represent a 10-bit bitmap. The first byte represents the first 8-bit of the bitmap. And the most-significant-bit of the first byte represents the first bit of the bitmap. The most-significant-bit of the second byte represents the 9-th bit of the bitmap. Suppose the bitmap is 0101010001, then the array content is {0x54, 0x40}.

  After we have inserted all m/k hash values of X, we proceed to calculate every yi in Y and check whether it *may* match any of the elements in the filter. This is done by mapping each yi into f positions using the same f hash functions and checking whether *all* f positions contain value 1. If so, yi is a probable match. We say the yi's match is probable because Bloom filter incurs false positives in that yi may be considered to equal to some of the m/k hash values even though it is not. Note that the correctness of this approach relies on the important property of Bloom filter that it never incurs false negatives. Thus, to confirm that yi is a real match, we check whether Y[i...i+k-1] is indeed identical to any of the X[0...k-1]_,_X[k...2k-1]... strings.

  Using a Bloom filter, our enhanced algorithm has a total runtime of O(m+n) (assuming there are not too many false positives), significantly faster than our previous two versions of approximate matching!
