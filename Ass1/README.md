Using a linked list data structure, design and develop an audiobook library system where a user list 
and audiobook list have to be maintained. Efficient management of audiobooks and user 
interactions, including listening progress, library management, and user preferences, should be the 
focus of this system. Quick access to audiobooks, effective tracking of users' listening progress, and 
support for user libraries and preferences should all be provided by the system. 
1. Generate a list of users with the following fieldsa. UserID (unique ID)
b. Name
c. Email
d. Preferences {User preferences, which could include preferred genres, authors, 
narrators, or other audiobook characteristics}
e. A linked list of audiobooks that the user has added to their library with timestamp 
and rating fields. ( timestamp, rating are initially 0) This list should be sorted based 
on audiobooks ID.
 The list should always be in sorted order according to UserID
2. Generate a list of audiobooks with the following fieldsa. AudiobookID: A unique identifier for each audiobook to facilitate easy referencing 
and management.
b. Title: The title of the audiobook.
c. Author: The name(s) of the author(s) of the audiobook.
d. Narrator: The person or people who narrate the audiobook.
e. Duration: The total length of the audiobook, typically in hours and minutes.
f. Genre: The category or type of content the audiobook falls under, such as fiction, 
non-fiction, science fiction, etc.
g. Rating: An average rating score, possibly on a scale from 1 to 5, reflecting user 
feedback and preferences.
The list should always be in sorted order according to AudiobookID
The following functions/operations need to be implemented:
1. Add_audiobook() and Edit_audiobook():
Input: Audiobook details including ID, title, author, narrator, duration, genre, and rating. 
And for edit : with Audiobook ID and the details that can be modified (e.g., title, author, 
duration).
Output: Confirmation message indicating the audiobook has been successfully added or 
modified to the library.
Note: Audiobooks will be inserted into the list in a sorted order based on title. If titles are 
the same, sort them by author.
2. Delete_audiobook():
Input: Criteria for identifying the audiobook to be deleted (e.g., title, author).
Output: A message indicating the audiobook is deleted.
Note: If the audiobook does not exist, indicate the deletion operation failed.
3. Search_audiobook():
Input: Search criteria (e.g., title, author, genre).
Output: List of audiobooks matching the criteria
4. Add_user_profile(): 
Input: User details including name, email, and preferences.
Output: A message indicating successful user account creation.
Note: Email addresses should remain unique within the system.
5. Add to User_library():
Input: User action (add/remove audiobooks to/from library), and audiobook details.
Output: Updated user library with a success or failure message.
Note: Each user's library should be a linked list, allowing for efficient management of their 
audiobooks without duplicates.
6. Listening_progress():
Input: User ID, audiobook ID, and new progress (timestamp or percentage).
Output: A message showing the updated listening progress for the specified audiobook.
Note: Ensure accurate tracking of listening progress for each user.
7. Display_user_libraries():
Input: User ID and filter criteria (e.g., all audiobooks, by genre).
Output: A list of audiobooks in the user's library matching the filter criteria.
Note: Allow users to view their audiobook collections based on different filters.
Note: Sort the report by listening time to highlight the most listened-to audiobooks.
8. Rate_Audiobook(): Allow users to rate an audiobook, contributing to its overall feedback 
score.
Input parameters: User ID, Audiobook ID, Rating (assuming a scale of 1 to 5).
Output: Confirmation message indicating the rating has been successfully recorded
9. Most_poplular_audiobook()
Input parameters: audiobook-ID
Output: Returns the title, author, and average rating of the most popular audiobook. If no 
audiobooks have been rated yet, it returns an appropriate message indicating no ratings are 
available to determine popularity.
10. Listening_history_report_user():
Input parameters: UserID
Output: A report detailing the audiobooks listened to, including titles, authors and total 
listening time.
11. Merge_user_libraries():
 Input: UserId’s for two user library to be merged.
Output: A single-user library containing the union of audiobooks from both libraries, sorted 
by title and author.
12. Listening_history_report_audiobook():
Input parameters: AudiobookID
Output: A report detailing the AudiobookID, title, author, and total listening time.
13. Display Audiobook List with the average rating in sorted order.
 
. 

