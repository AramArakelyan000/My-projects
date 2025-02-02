from fastapi import FastAPI, Request, Form, HTTPException, Response, Depends
from fastapi.templating import Jinja2Templates
from fastapi.responses import HTMLResponse, RedirectResponse
from sqlalchemy import create_engine, Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, Session
from typing import List
from pydantic import BaseModel
from fastapi.security import OAuth2PasswordBearer, OAuth2PasswordRequestForm
import re
import uuid
from datetime import datetime, timedelta

# Create a FastAPI application instance
app = FastAPI()
okno = False  # A global flag for UI purposes

# Database connection setup
SQLALCHEMY_DATABASE_URL = "mysql+mysqlconnector://aram:mheraram@localhost/mydatabase"
engine = create_engine(SQLALCHEMY_DATABASE_URL)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

# Define the base class for SQLAlchemy models
Base = declarative_base()

# Pydantic model for user output
class UserOut(BaseModel):
    id: int
    login: str
    password: str

# Define a model for storing links
class Links(Base):
    __tablename__ = "links"

    id = Column(Integer, primary_key=True, index=True)
    user_id = Column(Integer, ForeignKey('users.id'))
    link = Column(String(30))

# Define a model for users
class User(Base):
    __tablename__ = "users"

    id = Column(Integer, primary_key=True, index=True)
    login = Column(String(30))
    password = Column(String(30))

# Create a database session

def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

# Create all tables defined by the SQLAlchemy models
Base.metadata.create_all(bind=engine)

# Setup Jinja2 templates for rendering HTML
templates = Jinja2Templates(directory="templates")

# OAuth2 authentication setup
oauth2_scheme = OAuth2PasswordBearer(tokenUrl="token")

# Function to verify token and retrieve user (Stub implementation)
def get_current_user(token: str = Depends(oauth2_scheme), db: Session = Depends(get_db)):
    user = None
    return user

# Function to replace YouTube watch links with embed links
def replace_youtube_link(link: str) -> str:
    if 'watch?v=' in link:
        link = link.replace('watch?v=', 'embed/')
    return link

# Route to render registration page
@app.get("/register/", response_class=HTMLResponse)
async def register(request: Request):
    return templates.TemplateResponse("index.html", {"request": request, "first_name": '', "last_name": ''})

# Route to render login page
@app.get("/login/", response_class=HTMLResponse)
async def loginget(request: Request):
    return templates.TemplateResponse("login.html", {"request": request, "first_name": '', "last_name": ''})

# Route to handle registration form submission
@app.post("/register/", response_class=HTMLResponse)
async def submit_form(request: Request, first_name: str = Form(''), last_name: str = Form(''), db: Session = Depends(get_db)):
    if first_name == '' or last_name == '':
        prov = 1  # Error flag for empty input
        return templates.TemplateResponse("index.html", {"request": request, "first_name": first_name, "last_name": last_name, "prov": prov})
    
    users = db.query(User).all()
    for user in users:
        if first_name == user.login:
            prov = 2  # Error flag for duplicate username
            return templates.TemplateResponse("index.html", {"request": request, "first_name": first_name, "last_name": last_name, "prov": prov})
    
    user = User(login=first_name, password=last_name)
    db.add(user)
    db.commit()
    return templates.TemplateResponse("result.html", {"request": request, "first_name": first_name, "last_name": last_name})

# Route to handle login form submission
@app.post("/login/", response_class=HTMLResponse)
async def submit_form(request: Request, response: Response, form_data: OAuth2PasswordRequestForm = Depends(), db: Session = Depends(get_db)):
    username = form_data.username
    password = form_data.password
    
    if username == '' or password == '':
        prov = 1  # Error flag for empty input
        return templates.TemplateResponse("login.html", {"request": request, "first_name": username, "last_name": password, "prov": prov})
    
    user = db.query(User).filter(User.login == username, User.password == password).first()
    if user:
        session_id = str(uuid.uuid4())  # Generate session ID
        response.set_cookie(
            key="user",
            value=session_id,
            httponly=True,
            secure=True,
            samesite="Strict",
            expires=86400*365  # 1-year expiration
        )
        return RedirectResponse("/")
    
    prov = 3  # Error flag for incorrect credentials
    return templates.TemplateResponse("login.html", {"request": request, "first_name": username, "last_name": password, "prov": prov})

# Admin panel route
@app.get("/admin/", response_class=HTMLResponse)
async def admin(request: Request):
    return templates.TemplateResponse("admin.html", {"request": request})

# Admin login and user list retrieval
@app.post("/admin/", response_class=HTMLResponse)
async def admin(request: Request, first_name: str = Form(''), last_name: str = Form(''), db: Session = Depends(get_db)):
    if first_name == '' or last_name == '':
        prov = 1  # Error flag for empty input
        return templates.TemplateResponse("admin.html", {"request": request, "prov": prov})
    
    if (last_name == "admin") and (first_name == "admin"):
        users = db.query(User).all()
        users_text = "<h2>Users:</h2>"
        for user in users:
            user_links = db.query(Links).filter(Links.user_id == user.id).all()
            links = ', '.join([link.link for link in user_links])
            users_text += f"<p>ID: {user.id} | Login: {user.login} | Password: {user.password} | Links: {links}</p><br>"
        return HTMLResponse(content=users_text)
    
    prov = 4  # Error flag for unauthorized access
    return templates.TemplateResponse("admin.html", {"request": request, "prov": prov})

# Home route
@app.get("/", response_class=Response)
async def home(request: Request, db: Session = Depends(get_db)):
    user_cookie = request.cookies.get("user")
    return templates.TemplateResponse("result.html", {"request": request, "first_name": "", "okno": okno})
