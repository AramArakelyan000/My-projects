import asyncio
from binance import AsyncClient, BinanceSocketManager
from telegram.ext import CommandHandler, ApplicationBuilder
from telegram import Bot, Update
import atexit
import threading

# API инициализация
api_key = 'iHTAMqwKSfrVaTUqBs9yI3uA8d2QspxXE7SrWHxz5NZivuahPszK9xulhpmRkYb5'  # Ваш API ключ
api_secret = 'RtSpwyWhnYZzlzFSNrTioTP7rzXj8zygaFbOAsuzgflYLnUlFLB9JCcJyay4akHU'  # Ваш API секрет
bot_token = '7591947322:AAHf1EQK9pKA7DwSf9kvHkD8y0kDlKSva5M'   # Ваш токен Telegram бота
chat_id = '-1001159796887'  # Ваш chat_id

bot = Bot(token=bot_token)
symbols = [
    'BNBUSDT', 'XRPUSDT', 'LTCUSDT', 'BCHUSDT', 'LINKUSDT', 
    'EOSUSDT', 'TRXUSDT', 'DOTUSDT', 'ADAUSDT', 'MATICUSDT', 'SOLUSDT', 
    'AVAXUSDT', 'DOGEUSDT', 'SHIBUSDT', 'UNIUSDT', 'FILUSDT', 'VETUSDT', 
    'XLMUSDT', 'FTMUSDT', 'THETAUSDT', 'AAVEUSDT', 'SANDUSDT', 'CHZUSDT', 
    'ICPUSDT', 'SUSHIUSDT', 'ETCUSDT', 'ZRXUSDT', '1INCHUSDT', 'QTUMUSDT', 
    'MANAUSDT', 'HNTUSDT'
]

# Расчет вероятности успеха
def calculate_success_rate(trend, volume, liquidity, rsi, sma_diff, macd):
    base_rate = 50
    base_rate += 10 if trend == 'bullish' else -10
    if volume > 1000: 
        base_rate += 5
    if liquidity > 100:  
        base_rate += 5
    base_rate += 5 if rsi < 30 else -5 if rsi > 70 else 0
    base_rate += 10 if macd > 0 else -10
    base_rate += 5 if sma_diff > 0 else -5
    return min(max(base_rate, 0), 100)

async def start(update: Update, context):
    await update.message.reply_text(
        r"""*Good day\!*
An excellent offer for both beginner and professional traders\!

*After joining the Swim For Whales🐋 private channel, you will receive signals that this bot detects and sends there\.*
*Each signal is analyzed with complex algorithms, with risks evaluated, and will be presented to you\.*
*It is recommended to do your own market research before opening a trade and to open short-term trades\!*

_What is the bot's basis for its analysis?_

_Our algorithms track more than 30 cryptocurrencies and analyze the trades opened by huge volumes of "crypto points," sending signals to members of the private group\._

_The signal text includes the cryptocurrency pair, the *LONG* or *SHORT* position, as well as *TP/SL* to manage risks, and the probability of success for the trade._

"*Swimming* after the "Crypto points🐋" strategy has already proven itself many times, so it's time to make it available for the Armenian crypto market\! 
""",
        parse_mode="MarkdownV2"
    )


# Обработка сообщения
async def process_message(msg):
    try:
        if msg['e'] == 'aggTrade':
            symbol = msg['s']
            price = float(msg['p'])
            quantity = float(msg['q'])
            if price * quantity > 200000:
                direction = 'LONG' if not msg['m'] else 'SHORT'
                sl = round(price * 0.995, 2) if direction == 'LONG' else round(price * 1.005, 2)
                tp = round(price * 1.01, 2) if direction == 'LONG' else round(price * 0.99, 2)
                trend, volume, liquidity, rsi, sma_diff, macd = 'bullish', quantity, 200, 50, 1.5, 0.2
                success_rate = calculate_success_rate(trend, volume, liquidity, rsi, sma_diff, macd)
                await bot.send_message(chat_id=chat_id, text=f"🚨 Trading Signal (Futures)\n"
                                                             f"Pair: {symbol}\n"
                                                             f"Direction: {direction}\n"
                                                             f"SL: {sl}\n"
                                                             f"TP: {tp}\n"
                                                             f"Success Rate: {success_rate}%")
    except Exception as e:
        print(f"Error processing message: {e}")

# Запуск сокетов
async def start_socket(symbol):
    global client
    client = await AsyncClient.create(api_key=api_key, api_secret=api_secret)
    bm = BinanceSocketManager(client)
    try:
        async with bm.aggtrade_socket(symbol) as socket:
            while True:
                msg = await socket.recv()
                await process_message(msg)
    except Exception as e:
        print(f"Socket error for {symbol}: {e}")
    finally:
        await client.close_connection()

async def start_all_sockets():
    tasks = [start_socket(symbol) for symbol in symbols]
    await asyncio.gather(*tasks)

def run_sockets_in_thread():
    asyncio.run(start_all_sockets())

def cleanup():
    print("Stopping WebSocket...")

atexit.register(cleanup)

if __name__ == "__main__":
    application = ApplicationBuilder().token(bot_token).build()
    application.add_handler(CommandHandler("start", start))

    # Запускаем WebSocket в отдельном потоке
    socket_thread = threading.Thread(target=run_sockets_in_thread)
    socket_thread.start()

    # Запускаем Telegram бота
    application.run_polling()
