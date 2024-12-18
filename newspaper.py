import pandas as pd

# Input: Fixed constants
selling_price = 0.5  # Price per newspaper
lost_profit_rate = 0.33  # Loss per unsatisfied demand
scrap_value = 0.05  # Scrap value for leftover newspapers
supply = 70  # Number of newspapers available daily

# Simulated input data
data = {
    "Day": [1, 2, 3, 4, 5, 6, 7],
    "Random Digit for types News day": [94, 77, 49, 45, 43, 32, 49],
    "Types of news day":[0,0,0,0,0,0,0],
    "Random Digit for demand": [80, 20, 25, 88, 98, 66, 86],
}

# Create a DataFrame
df = pd.DataFrame(data)

# 1. Assign Types of News Day
def assign_news_day(x):
    if x <= 35:
        return "Good"
    elif x <= 80:
        return "Fair"
    else:
        return "Poor"

df["Types of news day"] = df["Random Digit for types News day"].apply(assign_news_day)

# Define the demand calculation function
def calculate_demand(day_status, random_digit):
    if day_status == "Good":
        if random_digit <= 3:
            return 40
        elif random_digit <= 8:
            return 50
        elif random_digit <= 23:
            return 60
        elif random_digit <= 43:
            return 70
        elif random_digit < 78:
            return 80
        elif random_digit <= 93:
            return 90
        elif random_digit <= 100:
            return 100
    elif day_status == "Fair":
        if random_digit <= 10:
            return 40
        elif random_digit <= 28:
            return 50
        elif random_digit <= 68:
            return 60
        elif random_digit <= 88:
            return 70
        elif random_digit <= 96:
            return 80
        elif random_digit <= 100:
            return 90
    elif day_status == "Poor":
        if random_digit <= 44:
            return 40
        elif random_digit <= 66:
            return 50
        elif random_digit <= 82:
            return 60
        elif random_digit <= 94:
            return 70
        elif random_digit <= 100:
            return 80
    return None  

# Apply the function to calculate the "Demand" column
df["Demand"] = df.apply(lambda row: calculate_demand(row["Types of news day"], row["Random Digit for demand"]), axis=1)






# 3. Calculate Revenue, Lost Profit, and Salvage from Scrap
df["Revenue from Sales"] = df["Demand"].apply(lambda x: x * selling_price)
df["Lost Profit"] = df["Demand"].apply(lambda x: (x - supply) * (selling_price-lost_profit_rate) if x > supply else 0)
df["Salvage from scrap"] = df["Demand"].apply(lambda x: (supply - x) * scrap_value if x < supply else 0)

# 4. Calculate Daily Profit
df["Daily Profit"] = (df["Revenue from Sales"] - (supply*lost_profit_rate) - df["Lost Profit"])+(df["Salvage from scrap"])

# Display the final table
print(df.head(7))
