int instance();

#ifdef MSVC
int WinMain() {
#else
int main() {
#endif
    instance();
}
