#ifndef CREATEAUTOMATEFORMPRESENTER_H
#define CREATEAUTOMATEFORMPRESENTER_H

class CreateAutomateForm;
class Algorithm;
class CreateAutomateFormPresenter
{
public:
    CreateAutomateFormPresenter(CreateAutomateForm * form, Algorithm * algorithm);

private:
    CreateAutomateForm * form;
    Algorithm * algorithm;
};

#endif // CREATEAUTOMATEFORMPRESENTER_H
