# FastAPI Web Application

This is a web application built using FastAPI, featuring user authentication, registration, and an admin panel. It connects to a MySQL database and utilizes Jinja2 templates for rendering HTML pages.

## Features
- User Registration and Login
- Admin Panel for Managing Users and Links
- OAuth2 Authentication with Session Cookies
- Secure Password Storage (Future Enhancement)
- MySQL Database Integration with SQLAlchemy
- Jinja2 Templates for Frontend Rendering
- YouTube Link Formatting for Embedded Videos

## Installation

### Prerequisites
- Python 3.8+
- MySQL Server
- Virtual Environment (Recommended)

### Setup
1. Clone the repository:
   ```sh
   git clone <repository_url>
   cd <project_directory>
   ```

2. Create and activate a virtual environment:
   ```sh
   python -m venv venv
   source venv/bin/activate  # On Windows use `venv\Scripts\activate`
   ```

3. Install dependencies:
   ```sh
   pip install -r requirements.txt
   ```

4. Configure database connection in the `SQLALCHEMY_DATABASE_URL` variable inside the script.

5. Run database migrations (if needed):
   ```sh
   python -m alembic upgrade head  # Optional, if using Alembic for migrations
   ```

6. Start the application:
   ```sh
   uvicorn main:app --reload
   ```

## API Endpoints

### Authentication
- `POST /login/` - User login via OAuth2 authentication.
- `POST /register/` - User registration.

### Admin Panel
- `GET /admin/` - Admin login page.
- `POST /admin/` - Displays a list of registered users (requires admin credentials).

### User Management
- `GET /` - Home page after login.
- `GET /register/` - User registration page.
- `GET /login/` - User login page.

## Database Models

### User
- `id`: Integer, Primary Key
- `login`: String (30)
- `password`: String (30)

### Links
- `id`: Integer, Primary Key
- `user_id`: Integer, ForeignKey to `users.id`
- `link`: String (30)

## Security Considerations
- **Current state:** Plaintext password storage (needs hashing like bcrypt)
- **Cookies:** Secure and HTTPOnly session cookies
- **Enhancements:** Implement JWT-based authentication

## License
This project is licensed under the MIT License.

## Author
Aram