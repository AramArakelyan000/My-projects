# Crypto Signal Bot

This is a Telegram bot that provides cryptocurrency trading signals based on real-time market data using the Binance API. The bot calculates and sends out trading signals (with specific details such as entry points, stop-loss (SL), take-profit (TP), and a calculated success rate) to a private Telegram channel.

## Features

- Real-time market data from Binance.
- Provides trading signals based on complex algorithms.
- Calculates success rates based on market indicators such as trend, volume, liquidity, RSI, SMA difference, and MACD.
- Telegram bot that sends trading signals directly to your group/channel.
- Supports multiple cryptocurrency pairs, including popular ones like `BNBUSDT`, `XRPUSDT`, `LTCUSDT`, and others.
  
## Installation

1. Clone this repository to your local machine.

2. Install the required Python packages:

```bash
pip install python-binance
pip install python-telegram-bot
```

3. Set up your Binance API credentials and Telegram bot token:
   - Replace the `api_key` and `api_secret` with your Binance API credentials.
   - Replace the `bot_token` with your Telegram bot token.
   - Replace the `chat_id` with the ID of your private Telegram channel or group.

```python
api_key = 'your_binance_api_key'
api_secret = 'your_binance_api_secret'
bot_token = 'your_telegram_bot_token'
chat_id = 'your_telegram_chat_id'
```

4. Run the bot script:

```bash
python bot.py
```

## How It Works

1. **Signal Calculation**: 
   - The bot listens to real-time aggregated trade data (`aggTrade`) for selected symbols on Binance. 
   - It calculates a success rate for each trade based on multiple factors like trend, volume, liquidity, RSI, SMA, and MACD.
   - If the trade volume exceeds a certain threshold (e.g., $200,000), the bot generates a signal with a suggested direction (LONG or SHORT), stop-loss (SL), and take-profit (TP) values.

2. **Message Handling**: 
   - When a signal is generated, the bot sends a message to the designated Telegram channel/group with the details of the trade signal and its calculated success rate.

3. **WebSocket Connection**: 
   - The bot uses WebSockets to listen to real-time trade data for multiple symbols simultaneously.
   - Each symbol has its own WebSocket connection, which runs in separate threads to handle multiple streams concurrently.

## Functions

- `start`: Handles the `/start` command in Telegram and sends a welcome message with information about the bot.
- `process_message`: Processes each incoming message from the WebSocket, calculates the success rate, and sends trade signals.
- `start_socket`: Initializes a WebSocket connection for each symbol and continuously listens for new data.
- `start_all_sockets`: Starts WebSocket connections for all supported symbols concurrently.
- `run_sockets_in_thread`: Runs the WebSocket listener in a separate thread to avoid blocking the main program.
- `cleanup`: Ensures proper cleanup when the program exits.

## Example Trading Signal

When the bot detects a suitable trade opportunity, it will send a message like this:

```
🚨 Trading Signal (Futures)
Pair: BTCUSDT
Direction: LONG
SL: 38500.00
TP: 39500.00
Success Rate: 85%
```

- **Pair**: The cryptocurrency pair for trading (e.g., `BTCUSDT`).
- **Direction**: The suggested trade direction, either `LONG` (buy) or `SHORT` (sell).
- **SL**: The stop-loss value, the price at which the position should be closed if the market goes against the trade.
- **TP**: The take-profit value, the price at which the position should be closed if the market moves in favor of the trade.
- **Success Rate**: The calculated probability of success based on market indicators.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

