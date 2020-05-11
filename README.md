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
|:------:|------|----------|:---:|
| :white_check_mark: | interfejs klienta (interakcja z użytkownikiem, wywoływanie funkcji bibliotecznych i reagowanie na nie) | :skull: |  |
| :white_check_mark: | dokończenie biblioteki, zrobienie wszystkich funkcji, reagowanie na błędy w Reply | :skull: |  |
| :white_check_mark: | obsługa błędów w ClientEndpoint, timeouty, ponowne wysyłanie | :skull: :skull: |  |
| :white_check_mark: | adresy, czyli po prostu wrappery na obsługę danych o adresie, przy okazji IpAddress w konstruktorze jak podamy stringa to wykona zapytanie do resolvera | :skull: |  |
| :white_check_mark: | dorobienie wszystkich Reply i Request, ich serializacja i deserializacja | :skull: :skull: |  |
| :white_check_mark: | serializacja i deserializacja komunikatów (Messages) | :skull: :skull: |  |
| :white_check_mark: | obsługa gniazda (czyli kod Socket) | :skull: :skull: |  |
| :white_check_mark: | implementacja handlerów czyli wykonanie żądań po stronie serwera | :skull: :skull: |  |
| :white_check_mark: | obsługa błędów po stronie serwera, timeouty, ponowne wysyłanie | :skull: :skull: |  |
| :white_check_mark: | sprawdzanie praw dostępu klientów, nadawanie naszych deskryptorów | :skull: |  |
| :white_check_mark: | kolejka handlerów i wątek wykonujący | :skull: :skull: :skull: |  |
| :white_check_mark: | wrzucanie SubEndpointów na nowe wątki | :skull: |  |
| :white_check_mark: | możliwość wyłączenia serwera i wyczyszczenia wszystkich zasobów (co może być upierdliwe, bo wątki mogą być zablokowane na czymś) | :skull: :skull: :skull: |  |