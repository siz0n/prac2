cout << "Общее решение:" << endl;
                    cout << "a = " << x0 << " + " << (b_coeff / gcd_val) << " * k" << endl;
                    cout << "b = " << y0 << " - " << (a_coeff / gcd_val) << " * k" << endl;
                    cout << "где k — любое целое число." << endl;void ferma(uint64_t a, uint64_t x, uint64_t  p )
 
                        cout << "Введите a: ";
                        cin >> a;
                        cout << "Введите x: ";
                        cin >> x;
                        cout << "Введите p: ";
                        cin >> p;
                        

                        if (!is_prime(p)) {
                            throw std::invalid_argument("p должно быть простым.");
                        }

                        if (gcd(a, p) != 1) {
                            throw std::invalid_argument("a и p должны быть взаимно просты.");
                        }

                        cout << "Результат (Ферма): " << fermat_method(a, x, p) << endl;
                        cout << "Результат (Бинарный): " << binary_exponentiation(a, x, p) << endl;

                        if (fermat_method(a, x, p) != binary_exponentiation(a, x, p)) {
                            throw std::runtime_error("Алгоритмы дали разные результаты.");
                        } else {
                            cout << "Результаты совпадают!" << endl;
                        }
                    } catch (const std::exception& e) {
                        cout << "Ошибка: " << e.what() << endl;
                    }
