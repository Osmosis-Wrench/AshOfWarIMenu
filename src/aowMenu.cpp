#pragma once

#include "aowMenu.h"

aowMenu::aowMenu()
{
	auto scaleformManager = RE::BSScaleformManager::GetSingleton();

	depthPriority = 0;

	menuFlags.set(RE::UI_MENU_FLAGS::kAlwaysOpen);
	menuFlags.set(RE::UI_MENU_FLAGS::kRequiresUpdate);
	menuFlags.set(RE::UI_MENU_FLAGS::kAllowSaving);
	inputContext = Context::kNone;

	if (uiMovie) {
		uiMovie->SetMouseCursorCount(0);  // disable input
	}

	scaleformManager->LoadMovieEx(this, MENU_PATH, [](RE::GFxMovieDef* a_def) -> void {
		a_def->SetState(RE::GFxState::StateType::kLog,
			RE::make_gptr<Logger>().get());
	});
}

void aowMenu::Register()
{
	auto ui = RE::UI::GetSingleton();
	if (ui) {
		ui->Register(MENU_NAME, Creator);
		aowMenu::Show();
	}
}

void aowMenu::Show()
{
	auto msgQ = RE::UIMessageQueue::GetSingleton();
	if (msgQ) {
		msgQ->AddMessage(aowMenu::MENU_NAME, RE::UI_MESSAGE_TYPE::kShow, nullptr);
	}
}

void aowMenu::Hide()
{
	auto msgQ = RE::UIMessageQueue::GetSingleton();
	if (msgQ) {
		msgQ->AddMessage(aowMenu::MENU_NAME, RE::UI_MESSAGE_TYPE::kHide, nullptr);
	}
}

void aowMenu::SetName(RE::GFxValue newName)
{
	RE::GPtr<RE::IMenu> menuObject = RE::UI::GetSingleton()->GetMenu(aowMenu::MENU_NAME);
	if (!menuObject || !menuObject->uiMovie) {
		logger::warn("AOWMenu tried to set name, but menuObject did not exist.");
		return;
	}
	menuObject->uiMovie->Invoke("ash.setText", nullptr, &newName, 1);
}

void aowMenu::SetLocation()
{
#if false
	// replace Settings::GetSingleton() with easyToml equivalent
	const RE::GFxValue widget_xpos = Settings::GetSingleton()->widget_xpos;
	const RE::GFxValue widget_ypos = Settings::GetSingleton()->widget_ypos;
	const RE::GFxValue widget_rotation = Settings::GetSingleton()->widget_rotation;
	const RE::GFxValue widget_xscale = Settings::GetSingleton()->widget_xscale;
	const RE::GFxValue widget_yscale = Settings::GetSingleton()->widget_yscale;
	RE::GFxValue posArray[5]{ widget_xpos, widget_ypos, widget_rotation, widget_xscale, widget_yscale };
	menuObject->uiMovie->Invoke("ash.setLocation", nullptr, posArray, 5);
#endif
}

#if false
// dont really need this for aow atm, but might later on if more is added.
void aowMenu::Update()
{

}
#endif

// Every time a new frame of the menu is rendered call the update function.
void aowMenu::AdvanceMovie(float a_interval, std::uint32_t a_currentTime)
{
	//aowMenu::Update();
	RE::DebugNotification("ass");
	RE::IMenu::AdvanceMovie(a_interval, a_currentTime);
}

