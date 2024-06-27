Using tree data structure, design and develop an audiobook library system where a user database 
and audiobook database have to be maintained. Efficient management of audiobooks and user 
interactions, including listening progress, library management, and user preferences, should be the 
focus of this system. Quick access to audiobooks, effective tracking of users' listening progress, and 
support for user libraries and preferences should all be provided by the system. 
Data Structures 
 User Tree: Manage user profiles using the chosen tree data structure. Each user node 
should contain: 
o UserID (unique ID) 
o Name 
o Email 
o Preferences (genres, authors, narrators, etc.) 
o A reference to another tree for the user's audiobook library, sorted by AudiobookID. 
 Audiobook Tree: Manage audiobooks using the chosen tree data structure. Each 
audiobook node includes: 
o AudiobookID (unique identifier) 
o Title 
o Author 
o Narrator 
o Duration 
o Genre 
o Sum_Rating 
o Count_Rating( Total count of rating done eg: 4 users) 
 (Note: Sum_Rating and Count_Rating will further help to calculate the average rating 
of an audiobook) 
Required Functions/Operations 
The following functions/operations need to be implemented: 
1. Add_audiobook() and Edit_audiobook(): 
Input: Audiobook details including ID, title, author, narrator, duration, genre, and rating. 
And for edit: with Audiobook ID and the details that can be modified (e.g., title, author, 
duration). 
Output: Confirmation message indicating the audiobook has been successfully added or 
modified to the library. 
Note: Audiobooks will be inserted into the database sorted based on title. If titles are the 
same, sort them by author. 
2. Delete_audiobook(): 
Input: Criteria for identifying the audiobook to be deleted (e.g., title, author). 
Output: A message indicating the audiobook is deleted. 
3. Add_user_profile(): 
Input: User details including name, email, and preferences. 
Output: A message indicating successful user account creation. 
Note: Email addresses should remain unique within the system. 
4. Add to User_library(): 
Input: User action (add/remove audiobooks to/from library), and audiobook details. 
Output: Updated user library with a success or failure message. 
Note: Each user's library should be a tree, allowing for efficient management of their 
audiobooks without duplicates. 
5. Search_audiobook(): 
Input: Search criteria (e.g., title, author, genre). 
Output: List of audiobooks matching the criteria. 
Note: Provide options for flexible search criteria. 
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
Output: A report detailing the audiobooks listened to, including titles, authors, and total 
listening time. 
11. Merge_user_libraries(): 
 Input: UserId’s for two user library to be merged. 
Output: A single-user library containing the union of audiobooks from both libraries, using 
title and author as the key, first use title for the same title use author. 
12. Listening_history_report_audiobook(): 
Input parameters: AudiobookID 
Output: A report detailing the AudiobookID, title, author, and total listening time. 
13. Range_Search_Audiobook 
Search and print titles of audiobooks with ID which have audiobook IDs between audiobook 
id1 and audiobook id2. 
For implementing this application, it is desirable to use file handling. You can generate a .txt file for 
data input. The file should contain data for 5 users and 10 audiobooks. 

