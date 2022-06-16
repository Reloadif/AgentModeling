import pandas as pd
import matplotlib.pyplot as pyplot

ownData = pd.read_csv('C:\\Users\\fasti\source\\repos\\AgentBaseModeling\\AgentBaseModeling\\ModelingData.csv', header=None)
yandexSicks = pd.read_csv('C:\\Users\\fasti\source\\repos\\AgentBaseModeling\\AgentBaseModeling\\yandexSicks.csv', header=None)
yandexDeaths = pd.read_csv('C:\\Users\\fasti\source\\repos\\AgentBaseModeling\\AgentBaseModeling\\yandexDeaths.csv', header=None)

yandexSicks = yandexSicks.values[0]
yandexDeaths = yandexDeaths.values[0]

def calculateInDay(arr):
    res = []
    res.append(arr[0])

    for i in range(1, len(arr)):
        res.append(arr[i] - arr[i - 1])

    return res

def PlotDeaths():
    days = ownData.values[0]
    deaths = ownData.values[2]

    formatedYandexDeaths = yandexDeaths[:len(days)]
    plotYandexDeaths = calculateInDay(formatedYandexDeaths)

    pyplot.plot(days, deaths, label='Смоделированно')
    pyplot.plot(days, plotYandexDeaths, 'g', label='Данные от Yandex')

    pyplot.xlabel('Дни')
    pyplot.ylabel('Число умерших')

    pyplot.tight_layout()
    pyplot.legend()
    pyplot.show()

def PlotSicks():
    days = ownData.values[0]
    sicks = ownData.values[1]

    formatedYandexSicks = yandexSicks[:len(days)]
    plotYandexSicks = calculateInDay(formatedYandexSicks)

    pyplot.plot(days, sicks, label='Смоделированно')
    pyplot.plot(days, plotYandexSicks, 'g', label='Данные от Yandex')

    pyplot.xlabel('Дни')
    pyplot.ylabel('Число заболевших')

    pyplot.tight_layout()
    pyplot.legend()
    pyplot.show()

PlotDeaths()
PlotSicks()
