
# ASGN Telegram Bot

This project is a Telegram bot for managing cryptocurrency wallets, purchasing tariffs, and checking balances using the TRC-20 network. The bot interacts with users through an intuitive interface, allowing them to perform actions such as wallet top-ups, withdrawal requests, and tariff management.

## Features

- **Wallet Management**: 
  - Users can check their balance.
  - Link a wallet address for withdrawals.
  - Withdraw funds from their wallet (with a minimum withdrawal amount and a 10% fee).
  
- **Tariff Management**: 
  - Users can purchase tariffs and view the purchased tariffs list.
  - Tariff 1 offers a 7% daily income for 60 days.
  
- **Payment Verification**: 
  - Users send a payment screenshot for verification when topping up their wallet.
  - Payments are processed via the TRC-20 network.

- **Daily Earnings**: 
  - The bot automatically distributes daily earnings based on the user's purchased tariffs.

## Prerequisites

- Python 3.6+
- SQLite3
- Python libraries: `pyTelegramBotAPI`, `schedule`

You can install the required libraries by running:

```bash
pip install pyTelegramBotAPI schedule
```

## Setting Up

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/yourproject.git
   cd yourproject
   ```

2. Replace `YOUR_BOT_API_KEY` in the `bot = telebot.TeleBot('YOUR_BOT_API_KEY')` line with your actual Telegram Bot API key.

3. Create a SQLite database (`basa.sql`) if it doesn't exist, or use the one provided. The database will store user data, payment information, and tariff purchases.

## Database Schema

- **users**: Stores user information (user ID, coins, wallet address).
- **payments**: Stores payment information (user ID, payment photo ID).
- **payment_photos**: Stores payment photo IDs for verification.
- **withdrawal_requests**: Stores withdrawal requests (user ID, amount).
- **purchased_tariffs**: Stores information about the user's purchased tariffs.

## Running the Bot

To run the bot, simply execute the following command:

```bash
python bot.py
```

The bot will start listening for messages and interactions. It will process commands like `/start`, and handle user interactions using inline keyboards.

## Commands

- `/start`: Starts the bot and registers the user.
- `💸Wallet`: View wallet balance.
- `📥Top up wallet`: Instructions to top up your wallet and send a payment screenshot.
- `🪙Tariff 1`: Information about Tariff 1 (cost: 10 USDT, daily income 7%).
- `📊My tariffs`: View the list of purchased tariffs.
- `📤Withdraw funds`: Request a withdrawal of funds.

## Contribution

Feel free to fork the project, make improvements, and submit pull requests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---