#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include "main.hpp"

#include "fonts.hpp"
#include "util.hpp"
#include "platform_specific/windows.hpp"

bool checkOnline() {
  Logger *logger = Logger::getInstance();

  Response r = Get(Url{"http://icanhazip.com"}, Timeout{5000});

  const bool isOnline = r.text.length() > 0;
  if (isOnline)
    logger->info("Internet connected");
  else
    logger->warn("Internet not connected");

  return isOnline;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void PostBabyInit() {
  constants->init();
  if (!constants->configFileExists()) constants->createConfigFile();

  if (!fileExists(constants->getIniFilePath())) {
    std::ofstream iniFile(constants->getIniFilePath());
    iniFile << imguiIniFilePreset;
    iniFile.close();
  }
}



int main(int, char **) {
  if (!pfd::settings::available())
  {
    std::cout << "Portable File Dialogs are not available on this platform.\n";
    return 1;
  }

  auto onlineCheck =
      pool.enqueue([&] { constants->setOnlineStatus(checkOnline()); });
  auto initThread = pool.enqueue([&] { PostBabyInit(); });

#if _WIN32
  ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
  // std::unique_ptr<FontManager> fm{new FontManager()};
  // auto loadFonts = pool.enqueue([&] { fm->loadFonts(); });

  const char *glsl_version = "#version 150";
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit()) return 1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef __APPLE__
  // GL 3.2 + GLSL 150
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Required on Mac
  glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#elif _WIN32
  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  float xscale, yscale;
  glfwGetMonitorContentScale(monitor, &xscale, &yscale);
  if (xscale > 1 || yscale > 1) {
    constants->highDPIscaleFactor = xscale;
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
  }

#else
  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  float xscale, yscale;
  glfwGetMonitorContentScale(monitor, &xscale, &yscale);
  if (xscale > 1 || yscale > 1) {
    constants->highDPIscaleFactor = xscale;
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
  }
#endif
  initThread.get();

  constants->setFontPath(absoluteFontPath());

  GLFWwindow *window =
      glfwCreateWindow(constants->WINDOW_WIDTH, constants->WINDOW_HEIGHT,
                       WINDOW_TITLE, NULL, NULL);
  if (window == NULL) return 1;
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);  // Enable vsync

  glfwSetKeyCallback(window, keyCallback);

  // Set this to true so GLEW knows to use a modern approach to retrieving
  // function pointers and extensions
  glewExperimental = GL_TRUE;
  const bool glewErr = glewInit();

  if (glewErr) {
    std::cerr << "Failed to initialize OpenGL loader\n";
    return 1;
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  constants->setTheme();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  ImGuiStyle &style = ImGui::GetStyle();
  style.ScaleAllSizes(constants->highDPIscaleFactor);

  io.IniFilename = constants->getIniFilePath();

  io.Fonts->AddFontFromFileTTF(
      constants->PATH_TO_FONT.c_str(),
      (constants->FONT_SIZE) * constants->highDPIscaleFactor, NULL, NULL);
  // loadFonts.get();

  // fm->setSelectedFontFromPath(constants->getFontPath());

  io.Fonts->AddFontFromFileTTF(
      constants->getFontPath(),
      (constants->FONT_SIZE) * constants->highDPIscaleFactor, NULL, NULL);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glViewport(0, 0, constants->WINDOW_WIDTH, constants->WINDOW_HEIGHT);
  glfwSetWindowSize(window, constants->WINDOW_WIDTH, constants->WINDOW_HEIGHT);

  GUI gui;
  // gui.setFont(std::move(fm));
  int display_w, display_h;

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    gui.render();

    ImGui::Render();

    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(constants->clear_color.x, constants->clear_color.y,
                 constants->clear_color.z, constants->clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap the screen buffers
    glfwSwapBuffers(window);
  }
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  onlineCheck.get();

  glfwDestroyWindow(window);
  glfwTerminate();

  constants->setWindowDimension(display_w, display_h);
  constants->writeConfig();

  return 0;
}
