const { app, BrowserWindow, Menu } = require("electron");
const path = require("path");

function createWindow() {
  const window = new BrowserWindow({
    width: 460,
    height: 860,
    minWidth: 380,
    minHeight: 700,
    title: "PULSE",
    backgroundColor: "#e4e6eb",
    autoHideMenuBar: true,
    webPreferences: { contextIsolation: true, sandbox: true }
  });
  Menu.setApplicationMenu(null);
  window.loadFile(path.join(__dirname, "index.html"));
}

app.whenReady().then(createWindow);
app.on("window-all-closed", () => app.quit());
