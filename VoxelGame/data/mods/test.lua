local current = 0.0

while current < 1.0 do
    Easing.EaseInBack(current)
    Easing.EaseOutBack(current)
    current = current + 0.05
end