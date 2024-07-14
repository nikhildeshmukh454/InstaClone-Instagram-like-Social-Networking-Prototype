# InstaClone: Instagram-like Social Networking Prototype

## Project Overview
InstaClone is a comprehensive social networking prototype inspired by Instagram. It showcases various key features such as user management, social networking functionalities, messaging, and content sharing.

## Key Features
### User Management
- **User Class:** Manages user accounts with unique email IDs, passwords, and user IDs.
- **Account Creation:** Ensures uniqueness of email IDs and user IDs using unordered_map for fast lookup.
- **Account Deletion:** Allows users to delete their accounts with password verification.
- **Profile Management:** Users can edit their bios and profile pictures.

### Social Networking
- **Followers and Following:** Users can follow/unfollow other users, and view lists of followers and following.
- **Friend Class:** Derived from User, allows viewing details of a friend's profile, posts, followers, and following.

### Messaging
- **Message Sending:** Enables users to send messages to each other using a stack-based approach, allowing for easy retrieval and management of chats.

### Content Sharing
- **Post Class:** Represents a user post with an image URL and caption.
- **Feed Management:** Users can post photos, which are automatically added to their followers' feeds.

## Skills Demonstrated
### Data Structures and Algorithms (DSA)
- Efficiently manages user data using unordered_map for fast lookups and stacks for managing message histories.
- Implements algorithms like password generation and validation.

### Object-Oriented Programming (OOP)
- Class Design: Utilizes classes to encapsulate data and behavior, promoting code reusability and modularity.
- Inheritance: Demonstrates inheritance to extend functionalities.

### Database Knowledge
- Data Management: Simulates database operations using unordered_map for user accounts and messaging.
- Persistence: Mimics account data persistence with data structures.

### System Design
- Scalability: Handles user interactions efficiently using data structures suited for quick operations.
- Modularity: Classes are designed to handle specific functionalities independently, enhancing maintainability and extensibility.

## Learning Outcomes
- Practical Application of DSA: Utilizes stacks for managing message history efficiently.
- OOP Principles: Implements encapsulation, inheritance, and potentially polymorphism through class design.
- Database Simulation: Uses unordered_map to simulate database operations.
- System Design Skills: Designs a scalable and modular system for social networking functionalities.

## Conclusion
InstaClone effectively implements key features similar to Instagram, combining DSA, OOP, database knowledge, and system design principles. It prepares developers for complex software development challenges by providing hands-on experience in a popular social media application context.
