#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

// Function to implement FIFO
int FIFO(int pages[], int numberOfPages, int numberOfFrame)
{
// To store current page information
unordered_set<int> currentPages;

// To store the pages in FIFO order
queue<int> queueFifo;

// Initializes to zero for first page
int pageFaults = 0;

// Loops till number of the pages
for (int c = 0; c < numberOfPages; c++)
{
// Check if the set can hold more pages
if (currentPages.size() < numberOfFrame)
{
// Check if current page is not already present in the set
// Insert it into set if not present
// already which represents page fault
if (currentPages.find(pages[c]) == currentPages.end())
{
currentPages.insert(pages[c]);

// Increase page fault counter by one
pageFaults++;

// Pushes the current page into the queue
queueFifo.push(pages[c]);
}// End of if condition
}// End of if condition

// Otherwise
else
{
// Check if current page is not already present in the set
if (currentPages.find(pages[c]) == currentPages.end())
{
// Removes the first page from the queue and stores it
int page = queueFifo.front();

// Pops the page from the queue
queueFifo.pop();

// Remove the page from the current pages
currentPages.erase(page);

// Insert the current page
currentPages.insert(pages[c]);

// Push the current page into the queue
queueFifo.push(pages[c]);

// Increase the page fault counter by one
pageFaults++;
}// End of if condition
}// End of else
}// End of for loop

// Returns number of page faults
return pageFaults;
}// End of function

// Function to find page faults using indexes
int LRU(int pages[], int numberOfPages, int numberOfFrames)
{
// To store the current pages.
unordered_set<int> currentPages;

// To store least recently used indexes of pages
unordered_map<int, int> pageIndexes;

// Initializes to zero for first page
int pageFaults = 0;

// Loops till number of pages
for (int c = 0; c < numberOfPages; c++)
{
// Check if the set can hold more pages
if (currentPages.size() < numberOfFrames)
{

// Check if current page is not already present in the set
// Insert the page if not present
// already which represents page fault
if (currentPages.find(pages[c]) == currentPages.end())
{
currentPages.insert(pages[c]);

// Increases the page fault by one
pageFaults++;
}// End of if condition

// Store the current used index of each page
pageIndexes[pages[c]] = c;
}// End of if condition

// Otherwise
else
{
// Check if current page is not already present in the set
if (currentPages.find(pages[c]) == currentPages.end())
{
// Find the least recently used pages that is present in the set
int lruPage = INT_MAX, page;

// Loops till end
for (auto it = currentPages.begin(); it != currentPages.end(); it++)
{
// Checks if recently used page is less than the lurPage
if (pageIndexes[*it] < lruPage)
{
// Assigns the recently used page
lruPage = pageIndexes[*it];
// Stores the page
page = *it;
}// End of if condition
}// End of for loop

// Remove the indexes page
currentPages.erase(page);

// Insert the current page
currentPages.insert(pages[c]);

// Increases page fault counter buy one
pageFaults++;
}// End of if condition

// Store the current used index of each page
pageIndexes[pages[c]] = c;
}// End of else
}// End of for loop

// Returns number of page faults
return pageFaults;
}// End of function

// Function to check whether a page exists in a frame or not
// returns true if present otherwise returns false
bool search(int page, vector<int> &frames)
{
// Loops till number of frames
for (int c = 0; c < frames.size(); c++)
// Checks if current frame is equals to parameter page returns true
if (frames[c] == page)
return true;

// At the end of the loop returns false for not found
return false;
}// End of function

// Function to find the frame that will not be used recently in future after given index
// in pages starting from 0 to number of pages minus one
int predict(int pages[], vector<int>& frames, int numberOfPages, int index)
{
// Store the index of pages which are going to be used recently in future
int resentFuture = -1, farthestPage = index;

// Loops till number of frames
for(int c = 0; c < frames.size(); c++)
{
int d;
// Loops till number of pages
for(d = index; d < numberOfPages; d++)
{
// Checks current contents of the frame is equals to current contents of the page
if(frames[c] == pages[d])
{
// Checks if d value is greater than the farthest page
if(d > farthestPage)
{
farthestPage = d;
resentFuture = c;
}// End of if condition
break;
}// End of if condition
}// End of for loop

// If a page is never referenced in future, return it.
if (d == numberOfPages)
return c;
}// End of for loop

// If all of the frames were not in future,
// return any of them, we return 0. Otherwise we return resentFuture.
return (resentFuture == -1) ? 0 : resentFuture;
}// End of function

// Function to implement optimal page replacement
void optimalPage(int pages[], int numberOfPages, int numberOfFrames)
{

// Create an array for given number of frames and initialize it as empty.
vector<int> frames;

// Traverse through page reference array and check for miss and hit.
int numberOfHit = 0;

// Loops till number of pages
for(int c = 0; c < numberOfPages; c++)
{

// Searches the page found in a frame then increase the hit count
if (search(pages[c], frames))
{
numberOfHit++;
continue;
}// End of if condition

// Checks if there is space available in frames pushes the page to frame
if (frames.size() < numberOfFrames)
frames.push_back(pages[c]);

// Otherwise find the page to be replaced.
else
{
int d = predict(pages, frames, numberOfPages, c + 1);
frames[d] = pages[c];
}// End of else
}// End of for loop

// Displays number of hit and number of miss
cout <<"\n Number of page fault: " <<numberOfPages - numberOfHit<<endl;
}// End of function

// main function definition
int main()
{
// Stores number of pages
int pages[] = {1,26,2,45,46,25,36,49,1,2,3,4,5,6,25,47,15,1,6,12,23,45,15,19,12,0,6,4,5,7,8,9,45,12,13,45,46,26,23,21,20,12,12,12,12,12,15,14,17,18,19,1,2,3,4,5,6,7,8,9,10,12,13,11,14,15,16,1,2,3,45,5,5,6,4,45,9,8,7,6,5,4,3,2,1,5,4,48,15,26,23,32,34,35,36,37,5,0,0,1};
// Calculates size
int numberOfPages = sizeof(pages)/sizeof(pages[0]);
// Stores number of frames
int numberOfFrames;

cin>>numberOfFrames;

// Calls the function and displays the result
cout<<"\n Number of page fault: "<<FIFO(pages, numberOfPages, numberOfFrames)<<endl;
cout<<"\n Number of page fault: "<<LRU(pages, numberOfPages, numberOfFrames)<<endl;
optimalPage(pages, numberOfPages, numberOfFrames);
return 0;
}// End of main function
