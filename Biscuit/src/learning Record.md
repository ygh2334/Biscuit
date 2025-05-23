#### 记录课程学习情况

#### 节数 课程名称 当前课程进度 日期




# 34节 (CAMERAS and How They Work) 已完成 5/13/2025
# 35节 (Creating an Orthographic Camera) 14:34 5/14/2025
# 35节 (Creating an Orthographic Camera) 26:00 5/20/2025
# 35节 (Creating an Orthographic Camera) 完成  5/21/2025
# 36节 (Moving to Sandbox) 8:40  5/22/2025
# 36节 (Moving to Sandbox) 完成  5/23/2025

# 这两种写法结果一致,lambda表达式更推荐了
# dispath.Dispatch<Biscuit::KeyPressedEvent>(std::bind(&ExampleLayer::OnKeyPressedEvent, this, std::placeholders::_1));
# dispath.Dispatch<Biscuit::KeyPressedEvent>([this](Biscuit::KeyPressedEvent& e) {return this->OnKeyPressedEvent(e); });
