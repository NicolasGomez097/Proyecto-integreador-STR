#ifndef RTC_H
#define RTC_H
int rtc_init(int speed);
void rtc_tick(void);
void rtc_close(void);
#endif