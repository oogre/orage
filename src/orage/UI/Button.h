//
//  Button.h
//  Orage
//
//  Created by Vincent Evrard on 7/07/21.
//

#ifndef Button_h
#define Button_h

#include "Plugable.h"
#include "IView.h"

/*
 toggle
 bang
*/
namespace ORAGE {
    namespace UI {
        using namespace std;
        using namespace ci;
        using namespace ci::gl;
        using json = nlohmann::json;
        
        class Button : public IView {
            typedef shared_ptr<class Button> ButtonRef;
            enum ButtonType {
                BANG,
                TOGGLE
            };
            ButtonType type = BANG;
            Button(string name, string type="Button") :
            IView(name, type)
            {
                setSize(Theme::ButtonSize);
                setBgColor(Theme::bgDisactiveColor);
                
                ORAGE::UI::ViewRef inputs = addView(Plugable::create("inputs"));
                inputs->setSize({getSize().x, 5});
                inputs->setPos({0, -7});
                inputs->as<Plugable>()->addPlug("input");
                
                ORAGE::UI::ViewRef outputs = addView(Plugable::create("outputs"));
                outputs->setSize({getSize().x, 5});
                outputs->setPos({0, getSize().y+2});
                outputs->anchor = TOP_LEFT;
                outputs->as<Plugable>()->addPlug("output");
                
                addEventListener("down", boost::bind(&Button::onDown, this, _1));
                addEventListener("up", boost::bind(&Button::onUp, this, _1));
                
            }
            bool onDown(COMMON::MouseEvent<IView> event){
                switch(type){
                    case BANG :
                        turnOn();
                        break;
                    case TOGGLE :
                        break;
                }
                return true;
            }
            bool onUp(COMMON::MouseEvent<IView> event){
                switch(type){
                    case BANG :
                        turnOff();
                        break;
                    case TOGGLE :
                        toggle();
                        break;
                }
                
                return true;
            }
        public :
            void turnOn(){
                module->setValue(module->getConf().at("on"));
            }
            void turnOff(){
                module->setValue(module->getConf().at("off"));
            }
            void toggle(){
                if(isOn()){
                    turnOff();
                }else{
                    turnOn();
                }
            }
            bool isOn(){
                return module->getValue() == module->getConf().at("on");
            }
            static ButtonRef create(string name){
                return ButtonRef( new Button(name) );
            }
            ButtonRef togglify(){
                type = TOGGLE;
                return as<Button>();
            }
            virtual ~Button() {
                removeEventListener("down", boost::bind(&Button::onDown, this, _1));
                removeEventListener("up", boost::bind(&Button::onUp, this, _1));
                module->removeEventListener("change", boost::bind(&Button::onChange, this, _1));
            }
            virtual void draw() override {
                pushModelView();
                IView::draw();
                popModelView();
            }
            virtual void setModule(CORE::ModuleRef module) override {
                View::setModule(module);
                module->addEventListener("change", boost::bind(&Button::onChange, this, _1));
                render();
            }
            void onChange(COMMON::Event<CORE::Module> event){
                render();
            }
            void render(){
                if(isOn()){
                    setBgColor(Theme::bgActiveColor);
                }else{
                    setBgColor(Theme::bgDisactiveColor);
                }
            }
        };//class Number : public IView {
        typedef shared_ptr<class Number> NumberRef;
    }//namespace UI {
}//namespace ORAGE {

#endif /* Button_h */
