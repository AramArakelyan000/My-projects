import telebot
from telebot import types
import sqlite3
import schedule
import time

WAITING_FOR_PAYMENT_PHOTO = 'waiting_for_payment_photo'
WAITING_FOR_WITHDRAW_AMOUNT = 'waiting_for_withdraw_amount'
WAITING_FOR_WALLET_ADDRESS = 'waiting_for_wallet_address'
user_states = {'state': None, 'wallet_address': None}
bot = telebot.TeleBot('6984946591:AAEtgf37fGKJEQkwMMyPhGsbaqa-o3MINFk')

markup = types.InlineKeyboardMarkup()
markup.add(types.InlineKeyboardButton('💸Кошелек', callback_data='my_coins'))
markup.add(types.InlineKeyboardButton('📥Пополнить кошелек', callback_data='button_2'))
markup.add(types.InlineKeyboardButton('🪙Тариф 1', callback_data='button_3'))
markup.add(types.InlineKeyboardButton('🧾О проекте', callback_data='button_4'))
markup.add(types.InlineKeyboardButton('📊Мои тарифы', callback_data='my_tariffs'))  

markup1 = types.InlineKeyboardMarkup()
markup1.add(types.InlineKeyboardButton('Купить', callback_data='buy'))

markup2 = types.InlineKeyboardMarkup()
markup2.add(types.InlineKeyboardButton('📤Вывод средств', callback_data='withdraw'))
markup2.add(types.InlineKeyboardButton('💳Привязанный кошельек', callback_data='kosh'))

def get_user_purchased_tariffs(user_id):
    with sqlite3.connect('basa.sql') as conn:
        cur = conn.cursor()
        cur.execute('SELECT tariff_name FROM purchased_tariffs WHERE user_id=?', (user_id,))
        result = cur.fetchall()
    return [tariff[0] for tariff in result] if result else []

def daily_earnings():
    with sqlite3.connect('basa.sql') as conn:
        cur = conn.cursor()
        cur.execute("SELECT user_id FROM users WHERE tarif1_end_date >= DATE('now')")
        users_tarif1 = cur.fetchall()

        for user_id in users_tarif1:
            current_points = get_user_points(user_id[0])
            set_user_points(user_id[0], current_points + 0.7)

def start_daily_earnings():
    schedule.every().day.at("00:00").do(daily_earnings)

    while True:
        schedule.run_pending()
        time.sleep(1)

def get_user_points(user_id):
    with sqlite3.connect('basa.sql') as conn:
        cur = conn.cursor()
        cur.execute('SELECT coins FROM users WHERE user_id=?', (user_id,))
        result = cur.fetchone()
    return result[0] if (result and result[0] is not None) else 0

def set_user_points(user_id, coins):
    try:
        conn = sqlite3.connect('basa.sql', check_same_thread=False)
        cur = conn.cursor()

        cur.execute('UPDATE users SET coins=? WHERE user_id=?', (coins, user_id))
        conn.commit()

    finally:
        conn.close()

@bot.message_handler(commands=['start'])

def start(message):
    user_id = message.from_user.id
    user_states[user_id] = None
    with sqlite3.connect('basa.sql') as conn:
        cur = conn.cursor()
        cur.execute('CREATE TABLE IF NOT EXISTS users (user_id INTEGER PRIMARY KEY, coins INTEGER DEFAULT 0, wallet_address TEXT)')
        cur.execute('CREATE TABLE IF NOT EXISTS payments (user_id INTEGER, photo_id TEXT)')
        cur.execute('CREATE TABLE IF NOT EXISTS payment_photos (id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER, photo_id TEXT)')
        cur.execute('CREATE TABLE IF NOT EXISTS withdrawal_requests (id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER, amount REAL)')
        cur.execute('CREATE TABLE IF NOT EXISTS purchased_tariffs (user_id INTEGER, tariff_name TEXT)')
        conn.commit()

        cur.execute("SELECT * FROM users WHERE user_id = ?", (user_id,))
        user_data = cur.fetchone()

        if not user_data:
            cur.execute("INSERT INTO users (user_id) VALUES (?)", (user_id,))
            conn.commit()
            bot.send_message(message.chat.id, f'id {user_id} вы успешно зарегистрировались, выберите кнопку ниже')
            coins = 0
        else:
            coins = user_data[1]

    bot.send_message(message.chat.id, '''

    Как часть ASGN Incorporated, наш проект воплощает в себе миссию компании - создание совершенно новых возможностей и привнесение инноваций в бизнес-мир. Мы стремимся к тому, чтобы наш проект стал неотъемлемой частью успеха ASGN Incorporated.''')
    bot.send_message(message.chat.id, f'id {user_id}: Баланс: {coins} USDT', reply_markup=markup)

    cur.close()

# Обработчик кнопок
@bot.callback_query_handler(func=lambda call: True)
def handle_callback(call):
    user_id = call.from_user.id

    if call.data == 'my_coins':
        coins = get_user_points(user_id)
        bot.send_message(call.message.chat.id, f'Баланс: {coins} USDT', reply_markup=markup2)

    elif call.data == 'kosh':
        user_states[user_id] = WAITING_FOR_WALLET_ADDRESS
        bot.send_message(call.message.chat.id, 'Введите адрес вашего кошелька USDT(TRC-20):')
        with sqlite3.connect('basa.sql', check_same_thread=False) as conn:
            cur = conn.cursor()
            cur.execute("INSERT INTO purchased_tariffs (user_id, tariff_name) VALUES (?, ?)", (user_id, 'Тариф 1'))
            conn.commit()

    elif call.data == 'withdraw':
        # Проверка, связан ли у пользователя кошелек
        with sqlite3.connect('basa.sql') as conn:
            cur = conn.cursor()
            cur.execute('SELECT wallet_address FROM users WHERE user_id=?', (user_id,))
            wallet_address = cur.fetchone()

            if wallet_address and wallet_address[0]:  # Пользователь имеет привязанный кошелек
                coins = get_user_points(user_id)
                if coins < 10:
                    bot.send_message(call.message.chat.id, 'Минимальная сумма для вывода - 10 USDT. Пополните свой баланс.')
                else:
                    user_states[user_id] = WAITING_FOR_WITHDRAW_AMOUNT
                    bot.send_message(call.message.chat.id, 'Введите сумму для вывода (не менее 10 USDT) Комиссия: 10%:')
            else:
                bot.send_message(call.message.chat.id, 'У вас нет привязанного кошелька. Пожалуйста, привяжите кошелек.')
    elif call.data == 'my_tariffs':
        # Add logic to retrieve and display purchased tariffs for the user
        # You can query your database for this information and send it as a message.
        # Example:
        purchased_tariffs = get_user_purchased_tariffs(user_id)
        if purchased_tariffs:
            tariffs_message = "Ваши купленные тарифы:\n"
            for tariff in purchased_tariffs:
                tariffs_message += f"{tariff}\n"
            bot.send_message(call.message.chat.id, tariffs_message)
        else:
            bot.send_message(call.message.chat.id, 'У вас нет купленных тарифов.')

    elif call.data == 'button_2':
        user_states[user_id] = WAITING_FOR_PAYMENT_PHOTO
        bot.send_message(call.message.chat.id, '''
<b>ВАЖНО! СЛЕДУЙТЕ СТРОГО ПО ИНСТРУКЦИИ.</b>
ПОСЛЕ ПОПОЛНЕНИЯ ДЕНЬГИ НА БАЛАНС НАЧИСЛЯТСЯ В ТЕЧЕНИИ 5 ЧАСОВ

Отправьте сумму в любом размере на кошелек⬇️\n <code>TMbYmyhnVCvXjvg6bjzAiERpE7kUavg3mT</code> ПО СЕТИ TRC-20(Tron)

После чего отправьте скриншот оплаты тут

<i>Если средства не поступили на ваш счет в течении 5 часов, свяжитесь с поддержкой (ссылку можно найти в описании бота)</i>
''', parse_mode='HTML')

    elif call.data == 'button_3':
        bot.send_message(call.message.chat.id, 'Тариф 1. Цена 10 USDT\nСуточный доход 7% ~ 0.7 USDT\nЦикл 60 дней', reply_markup=markup1)

    elif call.data == 'buy':
        conn = sqlite3.connect('basa.sql')
        cur = conn.cursor()
        user_id = call.from_user.id
        coins = get_user_points(user_id)
        conn.commit()
        conn.close()

        if coins >= 10:
            current_points = get_user_points(user_id)
            set_user_points(user_id, current_points - 10)
            with sqlite3.connect('basa.sql', check_same_thread=False) as conn:
                cur = conn.cursor()
                cur.execute("INSERT INTO purchased_tariffs (user_id, tariff_name) VALUES (?, ?)", (user_id, 'Тариф 1'))
                conn.commit()
                bot.send_message(call.message.chat.id, 'Вы успешно купили тариф 1', reply_markup=markup)
        else:
            bot.send_message(call.message.chat.id, 'Недостаточно USDT, сначала пополните кошелек!', reply_markup=markup)

    elif call.data == 'button_4':
        bot.send_message(call.message.chat.id, '''
<b>ASGN Incorporated</b> - новый виток в нашем постоянно развивающемся портфеле проектов! Мы с гордостью представляем вам свежий взгляд на инновации и уникальные возможности.

Как часть <b>ASGN Incorporated</b>, наш проект воплощает в себе миссию компании - создание совершенно новых возможностей и привнесение инноваций в бизнес-мир. Мы стремимся к тому, чтобы наш проект стал неотъемлемой частью успеха <b>ASGN Incorporated</b>.

Присоединяйтесь к нам, и мы обеспечим вас уникальным опытом инвестирования, который принесет не только финансовую выгоду, но и удовлетворение от участия в новаторском проекте <b>ASGN Incorporated</b>. Будущее начинается сегодня, а ваша инвестиция - ключ к его блестящему развитию!
''', parse_mode='HTML')

@bot.message_handler(content_types=['photo'])
def handle_photo(message):
    user_id = message.from_user.id
    conn = sqlite3.connect('basa.sql')
    cur = conn.cursor()

    if message.photo and user_states.get(user_id) == WAITING_FOR_PAYMENT_PHOTO:
        file_id = message.photo[-1].file_id
        cur.execute("INSERT INTO payment_photos (user_id, photo_id) VALUES (?, ?)", (user_id, file_id))
        conn.commit()

        bot.send_message(message.chat.id, 'Скриншот принят. Ожидайте проверки.', reply_markup=markup)

        user_states[user_id] = None
    else:
        bot.send_message(message.chat.id, 'Нажмите кнопку "Пополнить кошелек" и следуйте инструкции.', reply_markup=markup)

@bot.message_handler(commands=['give_points'])
def give_points(message):
    admin_user_id = 925238030
    user_id = message.from_user.id

    if user_id != admin_user_id:
        bot.send_message(message.chat.id, "У вас нет прав для выполнения этой команды.")
        return

    args = message.text.split()[1:]
    if len(args) != 2 or not args[0].isdigit() or not args[1].isdigit():
        bot.send_message(message.chat.id, "Используйте команду следующим образом: /give_points <user_id> <amount>")
        return

    target_user_id = int(args[0])
    amount = int(args[1])

    current_points = get_user_points(target_user_id)
    set_user_points(target_user_id, current_points + amount)

    # Отправка сообщения пользователю
    bot.send_message(target_user_id, f'На ваш баланс начислен {amount} USDT')

    bot.send_message(message.chat.id, f"Очки успешно добавлены пользователю {target_user_id}. Текущий баланс: {current_points + amount}")


@bot.message_handler(commands=['view_photos'])
def view_photos(message):
    admin_user_id = 925238030
    user_id = message.from_user.id

    if user_id != admin_user_id:
        bot.send_message(message.chat.id, "У вас нет прав для выполнения этой команды.")
        return

    conn = sqlite3.connect('basa.sql')
    cur = conn.cursor()

    cur.execute("SELECT user_id, photo_id FROM payment_photos")
    photos = cur.fetchall()

    if photos:
        for photo in photos:
            bot.send_photo(message.chat.id, photo[1], caption=f"Фотография пользователя {photo[0]}")
    else:
        bot.send_message(message.chat.id, "Нет доступных фотографий.")

    conn.close()

@bot.message_handler(commands=['admin_view_users'])
def admin_view_users(message):
    admin_user_id = 925238030
    user_id = message.from_user.id

    if user_id != admin_user_id:
        bot.send_message(message.chat.id, "У вас нет прав для выполнения этой команды.")
        return

    conn = sqlite3.connect('basa.sql')
    cur = conn.cursor()

    cur.execute("SELECT user_id, coins FROM users")
    users = cur.fetchall()

    total_users = len(users)  # Подсчет общего числа зарегистрированных пользователей

    if users:
        users_info = "\n".join([f"Пользователь {user[0]}: {user[1]} USDT" for user in users])  
        bot.send_message(message.chat.id, f" {users_info}\nВсего пользователей: {total_users}")
    else:
        bot.send_message(message.chat.id, "Нет зарегистрированных пользователей.")

    conn.close()

@bot.message_handler(func=lambda message: user_states.get(message.from_user.id) == WAITING_FOR_WITHDRAW_AMOUNT)
def handle_withdraw_amount(message):
    user_id = message.from_user.id

    try:
        coins = get_user_points(user_id)
        withdraw_amount = float(message.text)
        
        if withdraw_amount < 10:
            bot.send_message(message.chat.id, 'Минимальная сумма для вывода - 10 USDT. Введите сумму заново:')
        elif withdraw_amount > coins:
            bot.send_message(message.chat.id, 'Недостаточно средств.')
        else:    
            current_points = get_user_points(user_id)
            
            conn = sqlite3.connect('basa.sql', check_same_thread=False)
            cur = conn.cursor()

            # Сохраняем заявку в базе данных
            cur.execute("INSERT INTO withdrawal_requests (user_id, amount) VALUES (?, ?)", (user_id, withdraw_amount))
            conn.commit()

            # Уменьшаем баланс пользователя
            set_user_points(user_id, current_points - withdraw_amount)

            conn.close()

            bot.send_message(message.chat.id, f'Ваш запрос на вывод {withdraw_amount} USDT принят. Ожидайте обработки.')
            user_states[user_id] = None

    except ValueError:
        bot.send_message(message.chat.id, 'Некорректная сумма. Введите сумму заново:')



@bot.message_handler(commands=['admin_view_wallets'])
def admin_view_wallets(message):
    admin_user_id = 925238030
    user_id = message.from_user.id

    if user_id != admin_user_id:
        bot.send_message(message.chat.id, "У вас нет прав для выполнения этой команды.")
        return

    conn = sqlite3.connect('basa.sql')
    cur = conn.cursor()

    # Получаем пользователей, которые подали заявку на вывод
    cur.execute("SELECT DISTINCT user_id FROM withdrawal_requests")
    users_withdrawal_requests = cur.fetchall()

    if not users_withdrawal_requests:
        bot.send_message(message.chat.id, "Нет пользователей с заявками на вывод.")
        return

    users_info = ""
    for user in users_withdrawal_requests:
        user_id = user[0]
        cur.execute("SELECT wallet_address FROM users WHERE user_id = ?", (user_id,))
        wallet_address = cur.fetchone()

        if wallet_address:
            cur.execute("SELECT amount FROM withdrawal_requests WHERE user_id = ?", (user_id,))
            withdrawal_amount = cur.fetchone()
            withdrawal_amount = withdrawal_amount[0] if withdrawal_amount else 0
            users_info += f"Пользователь {user_id}: Кошелек - {wallet_address[0]}, Запрос на вывод - {withdrawal_amount} USDT\n"

    if users_info:
        bot.send_message(message.chat.id, users_info)
    else:
        bot.send_message(message.chat.id, "Нет привязанных кошельков у пользователей с заявками на вывод.")

    conn.close()


@bot.message_handler(func=lambda message: user_states.get(message.from_user.id) == WAITING_FOR_WALLET_ADDRESS)
def handle_wallet_address(message):

    user_id = message.from_user.id
    wallet_address = message.text

    # Сохраните адрес кошелька в базе данных
    try:
        conn = sqlite3.connect('basa.sql', check_same_thread=False)
        cur = conn.cursor()
        cur.execute('UPDATE users SET wallet_address=? WHERE user_id=?', (wallet_address, user_id))
        conn.commit()
        conn.close()

        bot.send_message(message.chat.id, f'Кошелек успешно привязан: {wallet_address}', reply_markup=markup)
        user_states[user_id] = None  # Сброс состояния после успешной привязки
    except Exception as e:
        bot.send_message(message.chat.id, f'Произошла ошибка при привязке кошелька: {e}', reply_markup=markup)

if __name__ == "__main__":
    # Запуск бота
    bot.polling(none_stop=True, interval=0)

    # Запуск ежедневного начисления в отдельном потоке
    daily_earnings_thread = threading.Thread(target=start_daily_earnings)
    daily_earnings_thread.start()