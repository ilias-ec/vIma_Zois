# Ομάδα: βΙμα Ζωής - Γυμνάσιο Κανήθου - Χαλκίδα
Συσκευή DiPUI

Disabled People Unit Information - Μονάδα Πληροφόρησης/Ενημέρωσης για ΑμεΑ και ηλικιωμένους με τη χρήση κατάλληλων διατάξεων και με πρόσβαση στο Διαδίκτυο. 
Η συσκευή:
■ θα βοηθάει στην ενημέρωση των ΑμεΑ σχετικά με τις συνθήκες διαβίωσης στο χώρο τους 
■ σε περίπτωση ανάγκης θα έχει τη δυνατότητα να καλεί με φωνητική κλήση ή/και με SMS κάποιο/α κοντινό/α πρόσωπο/α.

Η συσκευή θα αποτελείται από δύο μέρη:
- την Κεντρική Μονάδα:
    • ένα Arduino UNO
    • αισθητήρα θερμοκρασίας
    • αισθητήρα υγρασίας
    • αισθητήρα ατμοσφαιρικής πίεσης
    • αισθητήρα καθαρότητας του αέρα
    • αισθητήρα CO και άλλων αερίων.
    • RTC module (ημερομηνία και ώρα με δυνατότητα εύκολης πρόσβασης για την αλλαγή της μπαταρίας)
    • οθόνη 1.8 inch TFT LCD
    • ηχείο για την φωνητική απόδοση: α) της ημερομηνίας-ώρας (με επιλογή του χρήστη πατώντας ένα push button “Α”  και β) των μετρήσεων από τους αισθητήρες (με επιλογή του χρήστη πατώντας ένα διαφορετικό push button “Β” από αυτό της ημερομηνίας-ώρας)
    • βομβητή (buzzer)
    • κάρτα SIM για την περίπτωση ανάγκης ειδοποίησης ενός ή δυο κοντινών προσώπων με φωνητική κλήση και με συγκεκριμένο φωνητικό μήνυμα ή/και SMS με συγκεκριμένο λεκτικό κειμένου
    • ενσύρματο ή/και ασύρματο network module για ενημέρωση της συσκευής, ειδοποιήσεις, λήψη διαδικτυακών δεδομένων για τον καιρό και πιθανόν για άλλες μελλοντικές χρήσεις
    • SD κάρτα για αποθήκευση μετρήσεων κλπ
    • επιτοίχια ή επιτραπέζια τοποθέτηση 
    • τροφοδοσία 220V 

- το περικάρπιο (βραχιόλι):
    • ένα Arduino Nano
    • γυροσκόπιο και επιταχυνσιόμετρο για να αντιλαμβάνονται κάποιες συγκεκριμένες συνθήκες (π.χ. πτώση ή ακινησία για αρκετή ώρα) και να εκτελούν προκαθορισμένες λειτουργίες ή να στέλνουν συγκεκριμένη εντολή στην κεντρική μονάδα (π.χ. για αποστολή SMS σε προκαθορισμένους τηλεφωνικούς αριθμούς)
    • ένα ηχείο ενσωματωμένο στο περικάρπιο για την περίπτωση που ο χρήστης βρίσκεται μακριά από την κεντρική μονάδα
    • ένας αισθητήρας καρδιακών παλμών: στην περίπτωση που οι καρδιακοί παλμοί του χρήστη ανιχνευθούν εκτός των φυσιολογικών ορίων θα στέλνει ηχητική ειδοποίηση ή/και SMS σε προεπιλεγμένους τηλεφωνικούς αριθμούς
    • τροφοδοσία με μπαταρία λιθίου των 5 Volt. Θα ληφθεί ιδιαίτερη μέριμνα για την εύκολη αντικατάστασή της.

Εκτιμούμε ότι μια μέγιστη απόσταση 100 μέτρων από την Κεντρική Μονάδα θα είναι ικανοποιητική για την ασύρματη επικοινωνία μεταξύ Κεντρικής Μονάδας και περικαρπίου.

Μια μελλοντική βελτίωση της συσκευής θα μπορούσε να είναι η υποστήριξη δύο ή τριών περικαρπίων.


Η ομάδα ΒΙΜΑ Ζωής
Γυμνάσιο Κανήθου



Κατάλογος υλικών για την Κεντρική Μονάδα:
    • ένα Arduino UNO
    • αισθητήρας θερμοκρασίας-υγρασίας-ατμοσφαιρικής πίεσης - BMP280
    • αισθητήρα καθαρότητας του αέρα/CO – MQ-135
    • οθόνη 1.8 inch TFT LCD
    • ηχείο και φωνητική απόδοση: της ημερομηνίας-ώρας και των μετρήσεων των αισθητήρων ISD1820
    • βομβητής (buzzer)
    • για φωνητική κλήση και για SMS - A6 GPRS GSM Module - Quad-band 850 900 1800 1900MHZ + Antenna (AI Thinker)
    • ενσύρματο ή/και ασύρματο network - Ethernet Shield W5100 Network Board For Arduino ή/και ESP8266 ESP-12E UART WIFI Wireless Shield for Arduino
    • SD κάρτα για αποθήκευση μετρήσεων και RTC module – Data Logger shield with RTC and SD Card
    • τροφοδοτικό 12V DC- 220V AC

Κατάλογος υλικών για το περικάρπιο:
    • ένα Arduino Nano
    • γυροσκόπιο και επιταχυνσιόμετρο  - MPU-6050
    • ένα ηχείο - Small Speaker 8 Ohm 0.5W 40mm (ή μικρότερο)
    • ένας αισθητήρας καρδιακών παλμών - Heart Rate Pulse Sensor Module For Arduino
    • τροφοδοσία με μπαταρία λιθίου των 5 Volt.
