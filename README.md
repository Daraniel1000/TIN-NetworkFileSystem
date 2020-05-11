# TIN-NetworkFileSystem

Aplikacje klienta i serwera obsługujące prosty protokół NFS

## Budowanie

Z poziomu katalogu głównego:

```
./build.sh {client, server, mynfslib}
```

Utworzy się katalog ```cmake-build```, którym przechowywane będą pliki pośrednie budowania.

Pliki wykonywalne są umieszczone bezpośrednio w katalogach projektu, np. ```server/bin```.

## Zadania

| Status | Opis | Trudność | Kto |
|--------|------|----------|-----|
| [ ] | interfejs klienta (interakcja z użytkownikiem, wywoływanie funkcji bibliotecznych i reagowanie na nie) | :skull: |  |
| [ ] | dokończenie biblioteki, zrobienie wszystkich funkcji, reagowanie na błędy w Reply | :skull: |  |
| [ ] | obsługa błędów w ClientEndpoint, timeouty, ponowne wysyłanie | :skull: :skull: |  |
| [ ] | adresy, czyli po prostu wrappery na obsługę danych o adresie, przy okazji IpAddress w konstruktorze jak podamy stringa to wykona zapytanie do resolvera | :skull: |  |
| [ ] | dorobienie wszystkich Reply i Request, ich serializacja i deserializacja | :skull: :skull: |  |
| [ ] | serializacja i deserializacja komunikatów (Messages) | :skull: :skull: |  |
| [ ] | obsługa gniazda (czyli kod Socket) | :skull: :skull: |  |
| [ ] | implementacja handlerów czyli wykonanie żądań po stronie serwera | :skull: :skull: |  |
| [ ] | obsługa błędów po stronie serwera, timeouty, ponowne wysyłanie | :skull: :skull: |  |
| [ ] | sprawdzanie praw dostępu klientów, nadawanie naszych deskryptorów | :skull: |  |
| [ ] | kolejka handlerów i wątek wykonujący | :skull: :skull: :skull: |  |
| [ ] | wrzucanie SubEndpointów na nowe wątki | :skull: |  |
| [ ] | możliwość wyłączenia serwera i wyczyszczenia wszystkich zasobów (co może być upierdliwe, bo wątki mogą być zablokowane na czymś) | :skull: :skull: :skull: |  |