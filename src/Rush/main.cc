int main()
{
    auto screen = ScreenInteractive::Fullscreen();

    screen.TrackMouse(true);
    screen.Loop(nullptr);

    return EXIT_SUCCESS;
}
