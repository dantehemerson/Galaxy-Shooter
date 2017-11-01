#pragma once
#ifndef INTERFACE_HPP
#define INTERFACE_HPP

class Application;

class Interface {
public:
	Interface(Application*const app);
	virtual void draw() const = 0;
	virtual void update();
protected:
	Application* app;  // Puntero al único objeto
};

#endif // !INTERFACE_HPP