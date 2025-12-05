#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

void log_error(const char* message);
int safe_divide(int a, int b, int* result);
int calculate_square_root(double number, double* result);
double calculate_rectangle_area(double width, double height);
double calculate_value(double x);
int is_defined(double x);
void build_table(double start, double step, int count);
void find_extremum(double a, double b, double step);
void find_x_by_y(double target_y, double epsilon, double start, double end, double step);
void calculate_derivative(double x, double h);
double f(double x);
double f1(double x);
double f2(double x);
double f3(double x);

int main() {
    setlocale(LC_CTYPE, "RUS");
    int choice;

    printf("=== Анализ функции ===\n");

    do {
        printf("\nМЕНЮ:\n");
        printf("1. Значение функции в точке\n");
        printf("2. Таблица значений\n");
        printf("3. Поиск минимума/максимума\n");
        printf("4. Поиск X по Y\n");
        printf("5. Производная в точке\n");
        printf("0. Выход\n");
        printf("Выберите пункт меню: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода! Пожалуйста, введите число.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1: {
            double x;
            printf("Введите x: ");
            if (scanf("%lf", &x) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }

            if (!is_defined(x)) {
                printf("Функция не определена в этой точке.\n");
            }
            else {
                double result = calculate_value(x);
                if (isnan(result)) {
                    printf("Ошибка вычисления функции!\n");
                }
                else {
                    printf("f(%.2f) = %.6f\n", x, result);
                }
            }
            break;
        }

        case 2: {
            double start, step;
            int count;

            printf("Введите начало интервала: ");
            if (scanf("%lf", &start) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Введите шаг: ");
            if (scanf("%lf", &step) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Введите количество отсчетов: ");
            if (scanf("%d", &count) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }

            if (step <= 0 || count <= 0) {
                printf("Ошибка! Шаг и количество должны быть положительными.\n");
                break;
            }

            build_table(start, step, count);
            break;
        }

        case 3: {
            double a, b, step;

            printf("Введите начало отрезка: ");
            if (scanf("%lf", &a) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Введите конец отрезка: ");
            if (scanf("%lf", &b) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Введите шаг: ");
            if (scanf("%lf", &step) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }

            if (a >= b || step <= 0) {
                printf("Ошибка! Начало должно быть меньше конца, шаг > 0.\n");
                break;
            }

            find_extremum(a, b, step);
            break;
        }

        case 4: {
            double target_y, epsilon, start, end, step;

            printf("Введите значение Y: ");
            if (scanf("%lf", &target_y) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Введите точность: ");
            if (scanf("%lf", &epsilon) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Введите начало интервала поиска: ");
            if (scanf("%lf", &start) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Введите конец интервала поиска: ");
            if (scanf("%lf", &end) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Введите шаг поиска: ");
            if (scanf("%lf", &step) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }

            if (epsilon <= 0  || start >= end ||  step <= 0) {
                printf("Ошибка параметров!\n");
                break;
            }

            find_x_by_y(target_y, epsilon, start, end, step);
            break;
        }

        case 5: {
            double x, h;

            printf("Введите точку x: ");
            if (scanf("%lf", &x) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            printf("Введите шаг h: ");
            if (scanf("%lf", &h) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }

            if (h <= 0) {
                printf("Ошибка! h > 0.\n");
                break;
            }

            calculate_derivative(x, h);
            break;
        }

        case 0:
            printf("Выход из программы.\n");
            break;

        default:
            printf("Неверный выбор! Пожалуйста, выберите пункт от 0 до 5.\n");
            break;
        }
    } while (choice != 0);

    return 0;
}

void log_error(const char* message) {
    FILE* log_file = fopen("error.log", "a");
    if (log_file) {
        fprintf(log_file, "ERROR: %s\n", message);
        fclose(log_file);
    }
}

int safe_divide(int a, int b, int* result) {
    if (b == 0) {
        log_error("Попытка деления на ноль");
        return -1;
    }
    *result = a / b;
    return 0;
}

int calculate_square_root(double number, double* result) {
    if (number < 0) {
        log_error("Попытка извлечения корня из отрицательного числа");
        return -1;
    }
    *result = sqrt(number);
    return 0;
}

double calculate_rectangle_area(double width, double height) {
    if (width <= 0 || height <= 0) {
        log_error("Неверные размеры прямоугольника");
        return -1.0;
    }
    return width * height;
}

double calculate_value(double x) {
    if (!is_defined(x)) {
        log_error("Функция не определена в точке");
        return NAN;
    }
    return f(x);
}

int is_defined(double x) {
    if (x >= -1 && x < 2) {
        if (x == -1 || x == 1) {
            return 0;
        }
    }
    return 1;
}

void build_table(double start, double step, int count) {
    printf("\nТаблица значений функции:\n");
    printf("+----------+------------+\n");
    printf("|    x     |    f(x)    |\n");
    printf("+----------+------------+\n");
    double x = start;
    for (int i = 0; i < count; i++) {
        if (is_defined(x)) {
            double result = calculate_value(x);
            if (!isnan(result)) {
                printf("| %8.2f | %10.6f |\n", x, result);
            }
            else {
                printf("| %8.2f |   ошибка   |\n", x);
            }
        }
        else {
            printf("| %8.2f | не определ. |\n", x);
        }
        x += step;
    }
    printf("+----------+------------+\n");
}

void find_extremum(double a, double b, double step) {
    double min_x = a, min_val = INFINITY;
    double max_x = a, max_val = -INFINITY;
    int found = 0;

    printf("\nПоиск экстремумов на отрезке [%.2f, %.2f]:\n", a, b);

    for (double x = a; x <= b; x += step) {
        if (is_defined(x)) {
            double result = calculate_value(x);
            if (!isnan(result)) {
                if (result < min_val) {
                    min_val = result;
                    min_x = x;
                }
                if (result > max_val) {
                    max_val = result;
                    max_x = x;
                }
                found++;
            }
        }
    }

    if (found == 0) {
        printf("На отрезке функция нигде не определена или не может быть вычислена.\n");
    }
    else {
        printf("Минимум: f(%.4f) = %.6f\n", min_x, min_val);
        printf("Максимум: f(%.4f) = %.6f\n", max_x, max_val);
        printf("Найдено %d точек на отрезке.\n", found);
    }
}

void find_x_by_y(double target_y, double epsilon, double start, double end, double step) {
    printf("\nПоиск X для Y = %.6f с точностью %.6f:\n", target_y, epsilon);
    printf("в интервале [%.2f, %.2f] с шагом %.4f\n", start, end, step);

    int found = 0;

    for (double x = start; x <= end; x += step) {
        if (is_defined(x)) {
            double y = calculate_value(x);
            if (!isnan(y)) {
                if (fabs(y - target_y) < epsilon) {
                    printf("Найден X = %.6f, f(X) = %.6f (разность: %.6f)\n",
                        x, y, fabs(y - target_y));
                    found++;
                }
            }
        }
    }

    if (found == 0) {
        printf("Значений X, соответствующих Y = %.6f, не найдено.\n", target_y);
    }
    else {
        printf("Найдено %d значений X.\n", found);
    }
}

void calculate_derivative(double x, double h) {
    printf("\nВычисление производной в точке x = %.2f с шагом h = %.6f:\n", x, h);

    if (!is_defined(x) || !is_defined(x + h)) {
        printf("Функция не определена в этой точке.\n");
        return;
    }

    double fx = calculate_value(x);
    double fxh = calculate_value(x + h);

    if (isnan(fx) || isnan(fxh)) {
        printf("Ошибка вычисления функции!\n");
        return;
    }

    double derivative = (fxh - fx) / h;

    printf("f(%.6f) = %.6f\n", x, fx);
    printf("f(%.6f) = %.6f\n", x + h, fxh);
    printf("f'(%.2f) ≈ %.6f\n", x, derivative);
}

double f(double x) {
    if (x < -1) return f1(x);
    if (x < 2) return f2(x);
    return f3(x);
}

double f1(double x) {
    return 1.0 - exp(-x);
}

double f2(double x) {
    if (x == 1 || x == -1) {
        log_error("Деление на ноль в функции f2");
        return NAN;
    }

    int numerator_int = (int)(x * x + 1);
    int denominator_int = (int)(x * x - 1);
    int div_result;

    if (safe_divide(numerator_int, denominator_int, &div_result) != 0) {
        return NAN;
    }

    return (x * x + 1) / (x * x - 1);
}

double f3(double x) {
    double sum = 0.0;
    double factorial = 1.0;

    for (int n = 0; n <= 6; n++) {
        if (n == 0) {
            factorial = 1.0;
        }
        else {
            factorial *= n;
        }

        double sign = (n % 2 == 0) ? 1.0 : -1.0;
        double x_power = 1.0;
        for (int i = 0; i < n; i++) {
            x_power *= x;
        }

        double sqrt_value;
        if (calculate_square_root(factorial + 1, &sqrt_value) != 0) {
            log_error("Ошибка вычисления квадратного корня в f3");
            return NAN;
        }

        sum += sign * x_power / sqrt_value;
    }

    return sum;
}