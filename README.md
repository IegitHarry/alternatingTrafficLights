# 🚦 Sygnalizacja świetlna ze stałym cyklem – Arduino

Projekt cyklicznej sygnalizacji świetlnej dla skrzyżowania czterech dróg (górna, lewa, dolna, prawa) zrealizowany na Arduino. Światła zmieniają się w stałej kolejności, bez użycia czujników. Całość działa jako **nieblokująca maszyna stanów** oparta na `millis()`, więc w pętli głównej nie ma ani jednego `delay()`.

## ✨ Funkcje

- Obsługa 4 kierunków: górny, lewy, dolny, prawy
- Stały cykl: **górny → lewy → dolny → prawy → górny …**
- Tylko jeden kierunek ma zielone światło w danej chwili
- Przerwa „wszystko czerwone” (2 s) przed każdą zmianą kierunku
- Kod nieblokujący – czas liczony za pomocą `millis()`, bez `delay()`
- Czytelna struktura: osobna funkcja dla każdego stanu świateł

## 🧰 Wymagane elementy

| Element | Ilość |
|---|---|
| Arduino (np. Uno) | 1 |
| Dioda LED czerwona | 4 |
| Dioda LED zielona | 4 |
| Rezystor ok. 220 Ω | 8 |
| Płytka stykowa i przewody | – |

## 🔌 Schemat połączeń

| Kierunek | Dioda czerwona | Dioda zielona |
|---|---|---|
| Górny (`TOP`) | 7 | 6 |
| Lewy (`LEFT`) | 13 | 12 |
| Dolny (`BOTTOM`) | 11 | 10 |
| Prawy (`RIGHT`) | 9 | 8 |

Każdą diodę podłącz przez rezystor ok. 220 Ω do masy (GND).

## ⏱️ Przebieg cyklu

Każdy kierunek ma przydzielone **7 sekund**, podzielone na dwie fazy:

| Czas w obrębie fazy | Stan świateł |
|---|---|
| 0 – 2 s | Wszystkie kierunki czerwone |
| 2 – 7 s | Zielone dla aktualnego kierunku, pozostałe czerwone |

Po 7 sekundach program przechodzi do następnego kierunku i cykl zaczyna się od nowa. Pełny obieg wszystkich czterech kierunków trwa **28 sekund**.

## ⚙️ Jak to działa

Program korzysta z prostej maszyny stanów. Zmienna `state` przechowuje aktualny kierunek, a `newMillis` zapamiętuje moment wejścia w ten stan:

```cpp
#define OFF 0
#define TOP 1
#define LEFT 2
#define BOTTOM 3
#define RIGHT 4
```

W każdym obiegu `loop()` program sprawdza, ile czasu minęło od `newMillis`:

1. **≥ 7000 ms** – zapisz nowy czas startu i przejdź do następnego stanu.
2. **≥ 2000 ms** – włącz zielone światło dla bieżącego kierunku.
3. **w pozostałym czasie** – wywołaj `off()`, czyli wszystkie światła czerwone.

Przykład dla jednego kierunku:

```cpp
case TOP:
  if (millis() - newMillis >= 7000) {
    newMillis = millis();
    state = LEFT;
  }
  else if (millis() - newMillis >= 2000) {
    topOn();
  }
  else {
    off();
  }
  break;
```

Funkcje pomocnicze ustawiają odpowiednie piny:

- `topOn()`, `leftOn()`, `bottomOn()`, `rightOn()` – wyłączają czerwoną i włączają zieloną diodę wybranego kierunku
- `off()` – zapala wszystkie czerwone i gasi wszystkie zielone diody

Odejmowanie `millis() - newMillis` na typie `unsigned long` działa poprawnie również po przepełnieniu licznika `millis()` (po ok. 49,7 dnia).

## 🚀 Uruchomienie

1. Zepnij układ zgodnie z tabelą połączeń.
2. Otwórz plik z kodem w Arduino IDE (lub wklej go do symulatora, np. Tinkercad).
3. Wybierz właściwą płytkę i port.
4. Wgraj program. Cykl zacznie się od kierunku górnego.

## 🔧 Konfiguracja

Czasy są wpisane bezpośrednio w kodzie:

- `7000` – całkowity czas fazy jednego kierunku (ms)
- `2000` – długość fazy „wszystko czerwone” na początku każdej fazy (ms)

Czas zielonego światła to różnica obu wartości (domyślnie 5 s). Aby zmienić długość cyklu, podmień te liczby we wszystkich czterech blokach `case`. Wygodniej będzie wynieść je do stałych, np. `const unsigned long CYCLE_MS = 7000;` i `const unsigned long ALL_RED_MS = 2000;`.

## ⚠️ Uwagi

- Cykl jest **stały** – sygnalizacja nie reaguje na ruch i każdy kierunek dostaje zielone nawet wtedy, gdy nikt nie czeka.
- Funkcja `setup()` nie ustawia początkowego stanu pinów. Zaraz po starcie `loop()` wywołuje `off()`, więc krótkie, niezdefiniowane zachowanie diod trwa najwyżej ułamek sekundy.
- Definicja `OFF` jest zadeklarowana, ale nie jest używana w kodzie.

## 💡 Pomysły na rozwój

- Dodanie żółtego światła (np. migającego przed zmianą na zielone)
- Wynieść czasy do stałych lub zmiennych konfigurowalnych
- Dodanie czujników ruchu, aby pomijać kierunki bez pojazdów
- Tryb nocny (migające żółte światło)
- Przycisk dla pieszych

## 📄 Licencja

Projekt udostępniony na licencji MIT. Możesz go dowolnie używać, modyfikować i rozwijać.
